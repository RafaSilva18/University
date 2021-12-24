import javax.swing.*;
import java.io.*;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.Scanner;

public class MaquinaDinheiro {

    public int countcomp = 0;
    public  Compartimento[] comp;
    File file;
    Scanner scanner;
    String tipo;
    JOptionPane frame;
    boolean inter;

    public MaquinaDinheiro(String tipo) throws IOException {
        file = new File("produtosDinheiro.txt");
        scanner = new Scanner(file);
        comp = new Compartimento[20];
        frame = new JOptionPane();
        this.tipo = tipo;
        if(tipo.equals("interface")) {
            inter = true;
        }

        while(scanner.hasNext()){
            try {
                int quantidade = scanner.nextInt();
                String produto = scanner.next();
                String precouni = scanner.next();
                int compartimento = scanner.nextInt();
                comp[countcomp]=new Compartimento();
                comp[countcomp].quantidade = quantidade;
                comp[countcomp].produto = produto;
                comp[countcomp].precoUni = Double.parseDouble(precouni);
                comp[countcomp].compartimento = compartimento;
                countcomp++;
            } catch (Exception e) {
                if(inter){
                    JOptionPane.showInputDialog("Ocorreu um problema a transferir informação do ficheiro");
                }else
                    System.out.println("Ocorreu um problema a transferir informação do ficheiro");
            }
        }
    }

    public void sair() throws IOException { // reescreve o ficheiro atualizado para que quando corrermos o programa de novo estejam adicionados os produtos corretos
        try(FileWriter fw = new FileWriter("produtosDinheiro.txt",true);
            BufferedWriter bw = new BufferedWriter(fw);
            PrintWriter out = new PrintWriter(bw))
        {
            FileWriter a = new FileWriter("produtosDinheiro.txt");
            for(int i=0;comp[i]!=null;i++){
                out.print(comp[i].quantidade+" "+comp[i].produto+" "+comp[i].precoUni+" "+comp[i].compartimento+"\n");
            }

        } catch (IOException e) {
            if(inter){
                JOptionPane.showInputDialog("Ocorreu um problema");
            }else
                System.out.println("Ocorreu um problema");
            GestaoTexto();
        }
    }

    public void menuPrincipalTexto() throws IOException {
        Scanner s = new Scanner(System.in);
        int output = 0;
        if(inter){
            output = Integer.parseInt(JOptionPane.showInputDialog(frame,"0 - Sair\n1 - Gestão\n2 - Compra",JOptionPane.PLAIN_MESSAGE));
            System.out.println("\n");
        }else {
            s = new Scanner(System.in);
            System.out.println("0 - Sair");
            System.out.println("1 - Gestão");
            System.out.println("2 - Compra");
        }

        if(!inter) output = s.nextInt();

        switch (output){
            case 0 : if(inter) JOptionPane.showMessageDialog(frame,"Obrigado e volte sempre");else
                System.out.println("Obrigado e volte sempre");sair();break;
            case 1 : GestaoTexto();break;
            case 2 : Compra();break;
            default:if(inter) JOptionPane.showMessageDialog(frame,"Valor digitado não é possivel");else
                System.out.println("Valor digitado não é possivel");
                menuPrincipalTexto();
        }
    }

    public void GestaoTexto() throws IOException {
        Scanner s = new Scanner(System.in);
        int output = 0;
        if(inter){
            output = Integer.parseInt(JOptionPane.showInputDialog(frame,"0 - Voltar ao menu anterior\n1 - Carregamento de stock\n2 - Listagem de stock",JOptionPane.PLAIN_MESSAGE));
            System.out.println("\n");
        }else {
            System.out.println("0 - Voltar ao menu anterior");
            System.out.println("1 - Carregamento de stock");
            System.out.println("2 - Listagem de stock");
        }

        if(!inter) {
            output = s.nextInt();
        }

        switch (output){
            case 0 : menuPrincipalTexto();break;
            case 1 : CarregamentoStock();break;
            case 2 : ListagemStock();break;
            default:if(inter) JOptionPane.showMessageDialog(frame,"Valor digitado não é possivel");else
                System.out.println("Valor digitado não é possivel");
                GestaoTexto();
        }
    }

    public void CarregamentoStock() throws IOException {
        Scanner s = new Scanner(System.in);
        int quantidade = 0;
        String produto = "";
        String precoUni = "";
        int compartimento = 0;
        if(inter){
            String auxiliar;
            auxiliar = JOptionPane.showInputDialog(frame,"Insira a quantidade, produto, preço unitário e compartimento:",JOptionPane.PLAIN_MESSAGE);
            String[] teste = auxiliar.split("\s");
            quantidade = Integer.parseInt(teste[0]);
            produto = teste[1];
            precoUni = teste[2];
            compartimento = Integer.parseInt(teste[3]);
            System.out.println("\n");
        }else {
            System.out.println("Insira a quantidade, produto, preço unitário e compartimento: ");

            if (!inter) {
                quantidade = s.nextInt();
                produto = s.next();
                precoUni = s.next();
                compartimento = s.nextInt();
            }
        }

        boolean existe = true;
        for(int i = 0;comp[i]!=null;i++){
            if(comp[i].compartimento == compartimento){
                existe = false;
                if(produto.equals(comp[i].produto)){
                    this.comp[i].setQuantidade(this.comp[i].quantidade+quantidade);
                    if (inter) JOptionPane.showMessageDialog(frame,"Atualização concluida");else
                        System.out.println("Atualização concluida");
                }else
                if (inter) JOptionPane.showMessageDialog(frame,"Não pode adicionar dois produtos diferentes no mesmo compartimento");else
                    System.out.println("Não pode adicionar dois produtos diferentes no mesmo compartimento");break;
            }

        }
        if(existe) {
            comp[countcomp] = new Compartimento(quantidade, produto, Double.parseDouble(precoUni), compartimento);
            countcomp++;
            if (inter) JOptionPane.showMessageDialog(frame,"Itens adicionados com sucesso\n");else
                System.out.println("Itens adicionados com sucesso\n");
            try(FileWriter fw = new FileWriter("produtosDinheiro.txt", true);
                BufferedWriter bw = new BufferedWriter(fw);
                PrintWriter out = new PrintWriter(bw))
            {
                out.print("\n");
                out.print(quantidade+" "+produto+" "+precoUni+" "+compartimento);
            } catch (IOException e) {
                if (inter) JOptionPane.showMessageDialog(frame,"Ocorreu um problema");else
                    System.out.println("Ocorreu um problema");
                GestaoTexto();
            }
        }

        GestaoTexto();
    }


    public void ListagemStock() throws IOException {
        for(int i = 0;comp[i]!=null;i++){
            if (inter) JOptionPane.showMessageDialog(frame,"No compartimento "+comp[i].compartimento+" temos "+comp[i].produto+" a um preço unitário de "+comp[i].precoUni+"$ com "+comp[i].quantidade+" unidades");else
                System.out.println("No compartimento "+comp[i].compartimento+" temos "+comp[i].produto+" a um preço unitário de "+comp[i].precoUni+"$ com "+comp[i].quantidade+" unidades\n");
        }
        GestaoTexto();


    }

    public void Compra() throws IOException {
        Scanner s = new Scanner(System.in);
        Double[] dinheiro = new Double[20];
        String a;
        int compartimento;
        if(inter){
            a = JOptionPane.showInputDialog(frame,"Insira o dinheiro: ",JOptionPane.PLAIN_MESSAGE);
        }else {
            System.out.println("Insira o dinheiro: ");
            a = s.nextLine();
        }
        String[] teste = a.split("\s");
        for(int i = 0;i<teste.length;i++){
            dinheiro[i] = Double.parseDouble(teste[i]);
        }
        if(inter)compartimento = Integer.parseInt(JOptionPane.showInputDialog(frame,"Qual o compartimento?",JOptionPane.PLAIN_MESSAGE));
        else {
            System.out.println("Qual o compartimento?");
            compartimento = s.nextInt();
        }
        boolean existe = false;
        double dinheiroProduto = 0;
        int aux = 0 ;
        for(int i = 0 ;comp[i]!=null;i++){
            if(this.comp[i].compartimento == compartimento){
                existe = true;
                if(inter) JOptionPane.showMessageDialog(frame,"Produto Disponibilizado: "+this.comp[i].produto);else
                System.out.println("Produto Disponibilizado: "+this.comp[i].produto);
                dinheiroProduto = this.comp[i].precoUni;
                aux = i;
            }
        }
        if(!existe){
            if(inter) JOptionPane.showMessageDialog(frame,"Não existe produto no compartimento digitado\n");else
            System.out.println("Não existe produto no compartimento digitado\n");
            menuPrincipalTexto();
        }
        double dinheiroTotal = 0;
        for(int i = 0;dinheiro[i]!=null;i++){
                dinheiroTotal += dinheiro[i];
        }
        if(dinheiroTotal<dinheiroProduto){
            if(inter) JOptionPane.showMessageDialog(frame,"O dinheiro que inseriu não é suficiente para comprar este produto\nDinheiro devolvido com sucesso");
            else {
                System.out.println("O dinheiro que inseriu não é suficiente para comprar este produto");
                System.out.println("Dinheiro devolvido com sucesso");
            }
            menuPrincipalTexto();
        }
        double troco = 0;
        if(dinheiroProduto>0){
           troco = dinheiroTotal - dinheiroProduto + 0.001;  //+0.001 pois double não dá o valor certo , dá 0.1999999 em vez de 0.20
        }
        double[] trocado = {20,10,5,2,1,0.5,0.2,0.1,0.05,0.02,0.01};
        if(!inter)
        System.out.print("Troco: ");
        DecimalFormat df = new DecimalFormat("0.00");
        df.format(troco);
        double[] auxiliarTroco = new double[20];
        int aux5 = 0;
        for (int j = 0;j<trocado.length;j++){
            if(troco-trocado[j]>=0){
                System.out.print(trocado[j] +" ");
                String auxTroco = df.format(troco-trocado[j]);
                troco = Double.parseDouble(auxTroco.replace(",","."));
                auxiliarTroco[aux5] = trocado[j];aux5++;
                if(troco!=0) {
                    j = 0;
                }
            }
        }
        this.comp[aux].setQuantidade(this.comp[aux].quantidade-1);
        if(comp[aux].quantidade == 0){
            remove(aux);
        }
        if(inter)
        JOptionPane.showMessageDialog(frame, "Troco:\n"+Arrays.toString(auxiliarTroco));
        System.out.println("\n");
        menuPrincipalTexto();
        
    }

    public void remove(int compartimento) throws IOException {
         for(int i = 0;comp[i]!=null;i++){
             if(i == compartimento && comp[i+1]!=null){
                 comp[i] = comp[i+1];
                 comp[i+1] = null;
             }else if(comp[i+1] == null){
                 comp[i] = null;
             }
         }
         countcomp--;
         sair();
    }
}

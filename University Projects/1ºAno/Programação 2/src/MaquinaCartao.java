import javax.swing.*;
import java.io.*;
import java.util.Scanner;

public class MaquinaCartao{

    public int countcomp = 0;
    public  Compartimento[] comp;
    File file;
    Scanner scanner;
    String tipo;
    JOptionPane frame;
    boolean inter;


    public MaquinaCartao(String tipo) throws IOException {
        file = new File("produtosCartao.txt");
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
        try(FileWriter fw = new FileWriter("produtosCartao.txt",true);
            BufferedWriter bw = new BufferedWriter(fw);
            PrintWriter out = new PrintWriter(bw))
        {
            FileWriter a = new FileWriter("produtosCartao.txt");
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
            case 0 : if(inter) JOptionPane.showMessageDialog(frame,"Obrigado e volte sempre");else{
                System.out.println("Obrigado e volte sempre");}
                 sair();break;
            case 1 : GestaoTexto();break;
            case 2 : compraCartao();break;
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
                quantidade = s.nextInt();
                produto = s.next();
                precoUni = s.next();
                compartimento = s.nextInt();

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
            try(FileWriter fw = new FileWriter("produtosCartao.txt", true);
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

    public void compraCartao() throws IOException {
        Scanner s = new Scanner(System.in);
        int compartimento;
        int aux = 0;
        if(inter)
        compartimento = Integer.parseInt(JOptionPane.showInputDialog(frame,"Introduza o compartimento: ",JOptionPane.PLAIN_MESSAGE));
        else {
            System.out.println("Introduza o compartimento: ");
            compartimento = s.nextInt();
        }

        boolean existe = false;
        for(int i = 0 ;comp[i]!=null;i++){
            if(this.comp[i].compartimento == compartimento){
                existe = true;
                if (inter) JOptionPane.showMessageDialog(frame,"Produto Disponibilizado: "+this.comp[i].produto);else
                System.out.println("Produto Disponibilizado: "+this.comp[i].produto);
                aux = i;
            }
        }
        if(!existe){
            if (inter) JOptionPane.showMessageDialog(frame,"Não existe produto no compartimento digitado");else
            System.out.println("Não existe produto no compartimento digitado\n");
            menuPrincipalTexto();
        }
        if(existe) {
             this.comp[aux].setQuantidade(this.comp[aux].quantidade - 1);
             if (comp[aux].quantidade == 0) {
                 remove(aux);
             }
         }
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

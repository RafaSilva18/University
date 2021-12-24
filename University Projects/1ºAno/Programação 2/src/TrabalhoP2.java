import java.io.IOException;
import java.util.Scanner;

public class TrabalhoP2 {

    public static void main(String[] args) throws IOException {
         Scanner scanner = new Scanner(System.in);
         String s = "";
         String paga = "";
         while(true) {
             System.out.println("Deseja utlizar o programa por interface ou por comando ? ");
             s = scanner.next();
             if(s.equals("interface"))break;
             else if(s.equals("comando"))break;
         }
         while(true) {
             System.out.println("Qual o seu método de pagamento (cartão,dinheiro): ");
             paga = scanner.next();
             if(paga.equals("cartao"))break;
             else if(paga.equals("cartão"))break;
             else if(paga.equals("dinheiro"))break;
             else if(paga.equals("Dinheiro"))break;
         }
             if (paga.equals("dinheiro") || paga.equals("Dinheiro")) {
                 MaquinaDinheiro maquina = new MaquinaDinheiro(s);
                 maquina.menuPrincipalTexto();
             }else {
                 MaquinaCartao maquina = new MaquinaCartao(s);
                 maquina.menuPrincipalTexto();
             }
             return;
    }
}

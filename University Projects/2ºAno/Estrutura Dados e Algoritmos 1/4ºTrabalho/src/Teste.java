import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Teste {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        HashTable<String> a;
        String st = "";
        System.out.println("Insira o tamanho: ");
        int size = sc.nextInt();
        System.out.println("Qual o tipo de acesso ? (linear) (quadratico)");// necessario inserir um dos dois igual como está
        do{
            st = sc.next();
            if(st.equals("linear"))
                a = new LinearHashtable<>(size);
            else
                a = new QuadHashTable<>(size);

        }while(!st.equals("linear") && !st.equals("quadratico"));
        Corretor corretor = new Corretor(a);
        FileReader file = new FileReader("wordlist-big-20201212.txt");
        String s = null;
        BufferedReader bf = new BufferedReader(file);
        try {
            while ((s = bf.readLine())!= null) {
                a.insere(s);
            }
        }catch (IOException e){
            System.out.println("Algo correu mal");
        }
        String str = null;
        System.out.println("Insira o nome do ficheiro: ");
        String nomeFile = sc.next();
        FileReader file1 = new FileReader(nomeFile);
        BufferedReader bf1 = new BufferedReader(file1);
        try {
            while ((s = bf1.readLine())!= null) {
                corretor.verificarExiste(s); // insere no corretor cada linha do ficheiro
            }
        }catch (IOException e){
            System.out.println("Algo correu mal");
        }
    }
}

public class Teste {
    public static void main(String[] args){
         BigInt a = new BigInt("958");
         BigInt b = new BigInt("-56732");
        System.out.println("Resultado da soma: "+a.add(b));
        System.out.println("Resultado da subtração: "+a.sub(b));
        System.out.println("Resultado da multiplicação: "+a.mult(b));
        System.out.println("Resultado da divisão: "+a.div(b));
        System.out.println("Resultado da mod: "+a.mod(b));
    }
}

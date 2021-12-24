public class Corretor {
    public char[] arr;
    public HashTable<String> a;
    public int countAux;
    public String[] repetido; //utilizado para as sugestões nao se repetirem
    public int countRepetido;

    public Corretor(HashTable<String> a) {
        this.repetido = new String[1000];
        this.countRepetido = 0;
        this.countAux = 1;
        this.a = a;
        arr = new char[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 's', 't', 'u', 'v', 'x', 'z', 'r', 'q', 'ç', 'w', 'y', 'á', 'à', 'ú', 'ù', 'ó', 'ò', 'í', 'ì', 'é', 'è'};
    }

    public void verificarExiste(String b) {
        String[] arrS = b.split(" ");
        for (String j : arrS) {
            if (a.procurar(j) == null) {
                System.out.println("A palavra " + j + " não existe ou está mal escrita na linha " + countAux);
                adicionarLetra(j);
                retirarLetra(j);
                trocaLetra(j);
                System.out.println();
            }
            this.repetido = new String[1000];
            countRepetido = 0;
        }
        countAux++;
    }

    public void adicionarLetra(String key) {
        String aux = null;
        String str = null;

        for (int k = 0; k < arr.length; k++) { //Para adicionar no primeiro caracter
            str = arr[k] + key;
            if (a.procurar(str) != null && verRepetido(str)) {
                System.out.println("Sugestão: " + str);
                repetido[countRepetido] = str;
                countRepetido++;
            }
        }

        for (int i = 0; i < key.length(); i++) {//Para adicionar nos restantes
            str = String.valueOf(key.charAt(0));
            for (int f = 1; f < i + 1; f++)
                str = str + (key.charAt(f));
            for (int z = 0; z < arr.length; z++) {
                aux = str;
                str = str + arr[z];
                for (int x = i + 1; x < key.length(); x++) {
                    str = str + (key.charAt(x));
                }
                if (a.procurar(str) != null && verRepetido(str)) {
                    System.out.println("Sugestão: " + str);
                    repetido[countRepetido] = str;
                    countRepetido++;
                }
                str = aux;
            }
        }
    }

    public void retirarLetra(String key) {
        String str = "";
        String aux = null;
        for (int i = 0; i < key.length(); i++) {
            aux = str;
            for (int j = 0; j < i; j++)
                str = str + key.charAt(j);
            for (int z = i + 1; z < key.length(); z++)
                str = str + key.charAt(z);
            if (a.procurar(str) != null && verRepetido(str)) {
                System.out.println("Sugestão: " + str);
                repetido[countRepetido] = str;
                countRepetido++;
            }
            str = aux;
        }
    }

    public boolean verRepetido(String s) {// Para verificar se a sugestão já foi proposta
        for (String j : repetido) {
            if (j != null && j.equals(s))
                return false;
        }
        return true;
    }

    public void trocaLetra(String key) {
        String str = "";
        String aux = "";
        for (int i = 0; i < key.length(); i++) {
            aux = str;
            for (int j = 0; j < i; j++)
                str = str + key.charAt(j);
            if (i + 1 < key.length()) {
                str = str + key.charAt(i + 1);
                str = str + key.charAt(i);
            }
            for (int j = i + 2; j < key.length(); j++)
                str = str + key.charAt(j);
            if (a.procurar(str) != null && !str.equals(aux) && verRepetido(str)) {
                System.out.println("Sugestão: " + str);
            }
            str = aux;
        }
    }
}

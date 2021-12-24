public class Contactos implements Comparable<Contactos> {

    public String nome;
    ABP<Integer> contactos = new ABP<>();

    public Contactos(){}

    public Contactos(String nome , int NumeroTelefone){
        this.nome = nome;
        contactos.insere(NumeroTelefone);

    }

    public boolean procurarNumero(int Numero){
        for( int NumeroTelefone : contactos){
            if(NumeroTelefone == Numero){
                return true;
            }
        }
        return false;
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for(int NumeroTelefone : contactos){
            sb.append(NumeroTelefone+" ");
        }
        return sb.toString();
    }

    @Override
    public int compareTo(Contactos o) {
       return this.nome.compareTo(o.nome);
    }
}

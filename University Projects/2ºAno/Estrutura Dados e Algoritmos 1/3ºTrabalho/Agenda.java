public class Agenda {

    ABP<Contactos> agenda = new ABP<>();
    Contactos x;

    public void Adicionar(String nome ,int NumeroTelefone){
        x = new Contactos(nome.substring(0,1).toUpperCase()  + nome.substring(1),NumeroTelefone);
        agenda.insere(x);
  }

   public void EditarAdicionarNovoNumero(String nome,int NumeroTelefone){
        for(Contactos x : agenda){
            if((nome.substring(0,1).toUpperCase() + nome.substring(1)).equals(x.nome)){
                x.contactos.insere(NumeroTelefone);
            }
        }

   }

   public void EditarAdicionarNovoNumero(int numero , int NumeroTelefone){
       for(Contactos x : agenda){
           if(x.procurarNumero(numero)){
               x.contactos.insere(NumeroTelefone);
           }
       }
   }



    public void EditarNome(int NumeroTelefone ,String nome){
        for(Contactos x : agenda){
            if(x.procurarNumero(NumeroTelefone)) {
                Contactos aux = new Contactos();
                aux.nome = nome;
                aux.contactos = x.contactos;
                Remover(NumeroTelefone);
                agenda.insere(aux);
            }
        }
    }

    public void EditarNome(String nomeAntigo , String nome){
       for(Contactos x : agenda){
           if(x.nome.equals(nomeAntigo.substring(0,1).toUpperCase() + nomeAntigo.substring(1))) {
               Contactos aux = new Contactos();
               aux.nome = nome;
               aux.contactos = x.contactos;
               Remover(nomeAntigo);
               agenda.insere(aux);
           }
       }
    }

    public void EditarNumeroTelefone(int NumeroAntigo ,int NumeroTelefone){
        for(Contactos x : agenda){
            if(x.procurarNumero(NumeroAntigo)){
                x.contactos.remove(NumeroAntigo);
                x.contactos.insere(NumeroTelefone);
            }
        }

    }



   public void Remover(String nome){
        for(Contactos x : agenda){
            if((nome.substring(0,1).toUpperCase()  + nome.substring(1)).equals(x.nome)){
                agenda.remove(x);
            }
        }
   }

   public void Remover(int NumeroTelefone){
       for(Contactos x : agenda) {
           if (x.procurarNumero(NumeroTelefone)) {
               agenda.remove(x);
           }
       }
   }

    public String Chamador(int NumeroTelefone){
        System.out.print("A chamar : ");
        for (Contactos x : agenda){
            if(x.contactos.contains(NumeroTelefone)){
                System.out.println(x.nome + "\n");
                return x.nome;
            }
        }
        System.out.println("DESCONHECIDO \n");
        return "DESCONHECIDO";
    }

   public void Listar(){
        ABP<Contactos> novo = agenda;

       System.out.println("A sua lista : ");
       while (novo.raiz != null) {
           System.out.print(novo.findMin().nome + " ");
           for (Integer b : novo.findMin().contactos) {
               System.out.print(b + " ");
           }
           System.out.println();
           novo.remove(novo.findMin());
       }
    }



    @Override
    public String toString() {
        return agenda.toString();
    }
}

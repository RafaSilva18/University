public class Bus_Stop {
    public QueueArray<BusData> fila;
    BusData bus;
    public int passageiross;
    public int lugares;

    public int j = 0;
    public int[] arrTempo = new int[10] ;


    public Bus_Stop(int size){
        fila = new QueueArray<>(size);
    }


    public void chega_grupo(int hora , int minuto, int nPessoas){

        this.passageiross += nPessoas;
        System.out.println("Hora "+hora+":"+minuto+" "+nPessoas+" pessoas chegam, ficam "+passageiross+" na fila");
        bus = new BusData(nPessoas,hora,minuto);
        fila.enqueue(bus);

    }

    public  void chegada_bus(int horaB, int minutosB, int lugares){
        this.lugares = lugares;
        paragem(lugares,horaB,minutosB);

    }


    public void paragem(int lugaress,int horaB,int minutosB) {
        this.lugares = lugaress;
        int pessoas = 0;

        System.out.println("Chega Bus ->"+horaB+":"+minutosB+" há "+lugares+" lugares no bus");
        while (!fila.empty() && lugares != 0) {
            BusData primeiroQueue = fila.front();
            int passageiros = primeiroQueue.nPessoas;
            int pessoasChegaram = passageiros;
            if (lugares != 0) {
                pessoas = passageiros - lugares;
                if (pessoas <= 0) {
                    pessoas = 0;
                    fila.dequeue();
                } else {
                    primeiroQueue.setnPessoas(pessoas);

                }
                lugares -= passageiros;
                passageiross += pessoas - passageiros ;
                if (lugares < 0) lugares = 0;
            }

                System.out.println("Hora " + primeiroQueue.hora + ":" + primeiroQueue.minuto + " chegaram " + pessoasChegaram + " ficam " + pessoas);
              arrTempo[j]=(horaB*60+minutosB) - (primeiroQueue.hora*60 + primeiroQueue.minuto);
              j++;
            }
              int tempo = tempoMedio();
        System.out.println("tempo médio de espera: "+tempo+"m");
        int inicio = fila.ini;
        if(fila.ini != fila.fim) {
            fila.ini++;
            while (fila.ini != fila.fim && !fila.empty()) {
                BusData primeiroQueue = fila.front();
                System.out.println("Hora " + primeiroQueue.hora + ":" + primeiroQueue.minuto + " chegaram " + primeiroQueue.nPessoas + " ficam " + primeiroQueue.nPessoas);
                fila.ini++;
            }
            fila.ini = inicio;
        }


        }

        public int tempoMedio(){
        int soma = 0;
            for(int i=0;i<j;i++){
                soma +=arrTempo[i];
            }
            soma /= j;
            arrTempo = new int[10];
            j = 0;
            return soma;
        }

}

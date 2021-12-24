public class BusData {
    public int nPessoas;
    public int hora;
    public int minuto;


    public BusData(int nPessoas , int hora , int minuto){
        this.nPessoas = nPessoas;
        this.hora = hora;
        this.minuto = minuto;
    }

    public void setnPessoas(int nPessoas) {
        this.nPessoas = nPessoas;
    }

    @Override
    public String toString() {
        String s = hora+":"+minuto+" Grupo "+nPessoas+" pessoas";
        return s;
    }
}

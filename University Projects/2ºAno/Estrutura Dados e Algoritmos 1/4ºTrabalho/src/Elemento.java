public class Elemento<T>{
    public T valor;

    public Elemento(T x){
        valor = x;
    }

    public void setValor(T valor) {
        this.valor = valor;
    }

    public T getValor() {
        return valor;
    }
}

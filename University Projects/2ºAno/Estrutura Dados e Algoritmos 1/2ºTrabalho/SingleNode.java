public class SingleNode<T>{
    //variaveis
    T elemento;
    SingleNode<T> next;
    SingleNode<T> previous;

    //construtor
    public SingleNode(T x) {
        elemento = x;
        next = null;
        previous = null;
    }

    //construtor vazio
    public SingleNode() {
        this(null);
    }

    public SingleNode(SingleNode<T> previous , T y){
        this.previous = previous;
        next = null;
        elemento = y ;

    }

    //construtor com elemento e next
    public SingleNode(T x, SingleNode<T> n) {
        elemento = x;
        next = n;
    }

    public T element() throws InvalidNodeException{
        if(this==null){
            throw new InvalidNodeException("Null node");
        }
        return elemento;
    }

    public SingleNode<T> getPrevious(){
        return previous;
    }

    public void setPrevious(SingleNode<T> previous){
        this.previous = previous;
    }

    public SingleNode<T> getNext(){
        return next;
    }
    public void setElement(T x){
        this.elemento=x;
    }
    public void setNext(SingleNode<T> n){
        next=n;
    }
}

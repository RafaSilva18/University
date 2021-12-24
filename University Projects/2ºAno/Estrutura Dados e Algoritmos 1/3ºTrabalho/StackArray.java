import java.util.EmptyStackException;

public class StackArray<E> {
    E[] arr;
    private int size = 100;
    int top;

    public StackArray(){
        arr = (E[])new Object[size];
        this.top = -1;

    }

    void push(E o){
        if(size() == arr.length)
        top++;
        arr[top] = o;

    }

    E top(){
       return arr[top];
    }

    E pop(){
       if(!this.empty())
           return arr[top--];
       else{
           throw new EmptyStackException();
       }
    }

    int size(){
       return size;
    }

    boolean empty(){
       return top == -1;
    }
}

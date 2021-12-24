import java.util.Iterator;

public class DoubleLinkedList<T> implements Lista<T> {

    SingleNode<T> footer = new SingleNode<>();
    SingleNode<T> header = new SingleNode<>();
    private int theSize;

    public DoubleLinkedList(){
        header.setNext(footer);
        footer.setPrevious(header);

    }


    public SingleNode<T> header(){
        return header;
    }

    @Override
    public void add(T x) {
        SingleNode<T> n = new SingleNode<>(x);
        SingleNode<T> previous = footer.getPrevious();
        previous.setNext(n);
        n.setPrevious(previous);
        n.setNext(footer);
        footer.setPrevious(n);
        theSize++;
    }

    void add(SingleNode<T> prev, T x) {
        SingleNode<T> newNode =
                new SingleNode<T>(x, prev.getNext());
        prev.setNext(newNode);
        theSize++;
    }

    @Override
    public void add(int i, T x) {
        SingleNode<T> n = getNode(i - 1);
        add(n, x);

    }

    @Override
    public void set(int i, T x) {
        getNode(i).setElement(x);
    }

    @Override
    public T remove(int i) {
            SingleNode<T> n = getNode(i);
            SingleNode<T> antes = n.getPrevious();
            SingleNode<T> depois = n.getNext();
            antes.next = depois;
            depois.previous = antes;
            theSize--;
            return get(i);

    }

    @Override
    public void remove(T x) {
        SingleNode<T> n = header.getNext();
        SingleNode<T> antes = n.getPrevious();
        SingleNode<T> depois = n.getNext();
        while(n.element() != x){
            n = n.getNext();
        }

        antes.next = depois;
        depois.previous = antes;
        theSize--;
    }

    @Override
    public void clear() {
        header.next = footer;
        footer.previous = header;
        theSize = 0;
    }

    @Override
    public T get(int i) {
        if (i >= 0 && i <= size())
            return getNode(i).element();
        else
            throw new IndexOutOfBoundsException("getNode index: " + i + "; size: "
                    + size());
    }



    SingleNode<T> getNode(int i) {
        int indx = -1;
        SingleNode<T> s = header();
        while (indx++ < i) {
            s = s.getNext();
        }
        return s;
    }


    @Override
    public int size() {
        return theSize;
    }

    public SingleNode<T> findPrevious(T x) {
        SingleNode<T> p = header();
        for (T v : this) {
            if (v.equals(x)) return p;
            else p = p.getNext();
        }
        throw new java.util.NoSuchElementException();
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        SingleNode<T> no = header.getNext();
        s.append("[ ");
        while(no.next != null){
            s.append(no.elemento).append("  ");
            no = no.getNext();

        }
        s.append("]");
        return  s.toString();
    }


    @Override
    public Iterator<T> iterator() {
        return null;
    }
}

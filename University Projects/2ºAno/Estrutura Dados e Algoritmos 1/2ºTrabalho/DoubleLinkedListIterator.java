public class DoubleLinkedListIterator<E> implements java.util.Iterator<E> {
    private SingleNode<E> current ;

    public DoubleLinkedListIterator(SingleNode<E> c) {
        current = c;
    }

    @Override
    public boolean hasNext() {
        return current != null;
    }

    @Override
    public E next() {
        if (!hasNext())
            throw new java.util.NoSuchElementException();
        E nextItem = current.element();
        current = current.getNext();
        return nextItem;
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }
}

public class IteradorABP<E> implements java.util.Iterator<E> {
    NoABP<E> atual;
    StackArray<NoABP<E>> choice_points = new StackArray<NoABP<E>>();

    public IteradorABP(NoABP<E> x){
        atual=x;
        choice_points=new StackArray<NoABP<E>>();
    }


    @Override
    public boolean hasNext() {
        return atual != null;
    }

    public void remove( ){
        throw new UnsupportedOperationException();
    }

    @Override
    public E next() {
        if( !hasNext() )
            throw new java.util.NoSuchElementException( );
        E to_return=atual.getElemento();
        //salvaguardar a direita
        if (atual.getDir()!=null){
            choice_points.push(atual.getDir());
        }
        //atualizar a esquerda
        if(atual.getEsq()!=null){
            atual=atual.getEsq();
        }
        else{
            if(!choice_points.empty()){
                atual=choice_points.pop();
            }
            else
                atual=null; // its over
        }

        return to_return;
    }
}

public class ABP <E extends Comparable<? super E>> implements Iterable<E>{
    NoABP<E> raiz;

    public E findMin(){
        return findMin(raiz);
    }
    E findMin(NoABP<E> n){
            if (n.esq==null)
                return n.elemento;
            else
                return findMin(n.esq);
        }

        public boolean contains(E x){return contains(x,raiz);}

         boolean contains(E x, NoABP<E> n){
            if (n==null)
                return false;
            else{
                if (n.elemento.compareTo(x)<0)
                    return contains(x,n.dir);
                else
                if (n.elemento.compareTo(x)>0)
                    return contains(x,n.esq);
                else
                    return true;
            }
        }


        public void insere(E x){
           raiz = insere(x,raiz);
        }

        NoABP<E> insere(E x, NoABP<E> n){
            if (n==null)
                n=new NoABP<E>(x,null,null);
            else if ((n.elemento).compareTo(x)>0)
                n.esq=insere(x,n.esq);
            else if((n.elemento).compareTo(x)<0)
                n.dir=insere(x,n.dir);
            return n;
        }


        public void remove(E x){
           raiz = remove(x,raiz);
        }


         NoABP<E> remove( E x, NoABP<E> n)
        {
            if (n==null)
                return n;
            if (n.elemento.compareTo(x)<0)
                n.dir=remove(x,n.dir);
            else if(n.elemento.compareTo(x)>0)
                n.esq=remove(x,n.esq);
            else if (n.esq!=null && n.dir!=null){
                E min = findMin(n.dir);
                n.elemento = min;
                n.dir=remove(min,n.dir);
            }
            else if (n.esq==null)
                n=n.dir;
            else
                n=n.esq;
            return n;
        }


    @Override
    public java.util.Iterator<E> iterator() {
        return  new IteradorABP<E>(raiz);
    }

    @Override
    public String toString() {
        return raiz.toString();
    }

}

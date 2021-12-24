public class NoABP<E> {
    E elemento;
    NoABP<E> esq;
    NoABP<E> dir;


    NoABP(E e) {
        elemento = e;
        esq = null;
        dir = null;
    }


    NoABP(E e, NoABP<E> esq, NoABP<E> dir) {
        elemento = e;
        this.esq = esq;
        this.dir = dir;
    }

    public NoABP<E> getDir() {
        return dir;
    }

    public NoABP<E> getEsq() {
        return esq;
    }

    public E getElemento() {
        return elemento;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(elemento + " ");
            if (esq != null) {
                sb.append(esq.elemento + " ");
                elemento = esq.elemento;
                toString();
            }
            if (dir != null) {
                sb.append(dir.elemento + " ");
                elemento = dir.elemento;
                toString();
            }
        return sb.toString();
    }
}

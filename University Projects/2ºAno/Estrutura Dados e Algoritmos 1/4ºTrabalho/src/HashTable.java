public abstract class HashTable<T>{
    public Elemento<T>[] arr ;
    public int size;
    public int countAux = 0;

    public HashTable(){}

    public HashTable(int n) {
        size = n;
        arr = new Elemento[n];
    }

    public int ocupados(){
        int count = 0;
        for (Elemento j : arr) {
            if (j != null && j.valor != null) {
                count++;
            }
        }
        return count;
    }

    public float factorCarga(){
        return countAux / (float) size;
    }

    protected abstract int procPos(T s);

   public void alocarTabela(int dim) {
        arr = new Elemento[dim];
    }



    public void tornarVazia(){
        for (Elemento j : arr) {
            if(j!=null)
            j.valor = null;
        }
    }

    public T procurar(T x){
        int index = procPos(x);
        if(arr[index] != null && arr[index].valor.equals(x))
            return x;
        return null;
    }

    public void remove(T x){
        for (Elemento j : arr) {
            if (j != null && j.valor.equals(x)) {
                j.valor = null;
                break;
            }
        }
    }

    public void insere(T x){
        arr[procPos(x)] = new Elemento<>(x);
        countAux++;
        if(factorCarga()>=0.5){
            rehash();
        }
    }

    public void rehash() {
        int i = 2 * size;
        Elemento<T>[] arr1 = new Elemento[ocupados() + 1];
        int aux1 = 0;
        for (Elemento j : arr) {
            if (j != null) {
                arr1[aux1] = j;
                aux1++;
            }
        }
        size = i;
        arr = new Elemento[size];

        int z = 0;
        for (Elemento j : arr1) {
            if (j != null) {
                T a = arr1[z].valor;
                insere(a);
                z++;
            }
        }
    }

    public void print(){
        int i = 0;
        for(Elemento<T> j: arr){
            if(arr[i]!=null)
            System.out.println(i+": "+arr[i].getValor());
            else
                System.out.println(i+": "+"null");
            i++;
        }
    }
}

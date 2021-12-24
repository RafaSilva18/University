public class QuadHashTable<T> extends HashTable<T>{

    public QuadHashTable(int size){
        super(size);
    }

    @Override
    protected int procPos(T s) {
        int index = s.hashCode();
        int x = 1;
        index %= size;
        if (index < 0)
            index *= -1;
        if(arr[index] != null && arr[index].valor.equals(s))
            return index;
        while (arr[index] != null) {
            index += (x * x);
            if (index >= size)
                index = 0;
            if(arr[index] != null && arr[index].valor.equals(s))
                return index;
            x++;
        }

        return index;
    }
}

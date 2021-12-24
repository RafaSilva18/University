public class LinearHashtable<T> extends HashTable<T>{

    public LinearHashtable(int size){
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
                index += x;
                if (index >= size)
                    index = 0;
                if(arr[index] != null && arr[index].valor.equals(s))
                    return index;
                x++;
            }
            if(arr[index] != null && arr[index].valor.equals(s))
                return index;

            return index;
        }
}

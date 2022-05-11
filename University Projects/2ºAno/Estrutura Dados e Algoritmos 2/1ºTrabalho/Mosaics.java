import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in)); // Read input
        String[] colLn = input.readLine().split(" "); // Split the input line in Columns and Lines

        int lines = Integer.parseInt(colLn[0]);
        int columns = Integer.parseInt(colLn[1]);
        long[] arr = getArrayPieces(columns); // Array with the return of function table
        String line;
        char c;
        int count = 1;
        long finalValue = 1;
        char next = ' ';

        for (int i = 0; i < lines; i++) {
            line = input.readLine();
            for (int z = 0; z < line.length(); z++) {
                c = line.charAt(z);

                if (c != '.') {
                    for (int y = z + 1; y <= line.length() + 1; y++) {
                        if (y < line.length())
                            next = line.charAt(y);
                        if (c != next || y + 1 == line.length() + 1) {
                            finalValue *= arr[count];
                            count = 1;
                            z = y - 1;

                            break;
                        } else
                            count++;
                    }
                }
            }
        }
        System.out.println(finalValue);
    }

    public static long[] getArrayPieces(int bPiece) {
        int[] pieces = {1, 2, 3, 4, 6, 8, 10, 12, 16}; // Size of pieces of lego we can use

        long[] arr = new long[bPiece + 1]; // arr with sie bpiece + 1

        arr[0] = 1;

        for (int q = 1; q <= bPiece; q++){ // this for statement will put the possibilities of each piece until reaches bpiece in an array ex:([1,1,2,4,8...])
            long val = 0;
            for (int i = 0; i < pieces.length; i++) {
                int x = q - pieces[i];
                if (x >= 0)
                    val += arr[x];
                else
                    break;
            }
            arr[q] = val;
        }
        return arr;
    }
}

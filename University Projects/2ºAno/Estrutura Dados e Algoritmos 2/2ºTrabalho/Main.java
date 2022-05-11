import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.Queue;
import java.lang.Integer;

class Main {

    public static double distancia2d(double x1, double y1, double x2, double y2) {
        double a = x2 - x1;
        double b = y2 - y1;
        return Math.sqrt(Math.pow(a, 2) + Math.pow(b, 2));
    }

    public static ArrayList<holdPoint> beginNode(int reach, ArrayList<holdPoint> listOrderly) {
        ArrayList<holdPoint> holdPointBegin = new ArrayList<>(); // Lista com os holdPoints que podemos comeÃ§ar com

        for (Main.holdPoint holdPoint : listOrderly) {
            if (holdPoint.getY() <= reach)
                holdPointBegin.add(holdPoint);
            else
                break;
        }

        return holdPointBegin;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in)); // Read input

        String[] firstLine = input.readLine().split(" ");
        String[] holdPointLines;

        int n = Integer.parseInt(firstLine[0]); // Número de holding Points
        int h = Integer.parseInt(firstLine[1]); // Altura total
        int c = Integer.parseInt(firstLine[2]); // Número de casos de testes

        Graph g = new Graph(n);

        ArrayList<holdPoint> listOrderly = new ArrayList<>(); // Lista ordenada com holdPoints
        ArrayList<Integer> reachList = new ArrayList<>(); // Lista com todos os casos de teste

        for (int i = 0; i < n; i++) { // Cria um nó no grafo para cada holding point e adiciona a lista de pontos 
            holdPointLines = input.readLine().split(" ");
            holdPoint holdPoint = new holdPoint(Integer.parseInt(holdPointLines[0]),
                    Integer.parseInt(holdPointLines[1]));
            g.addNode(holdPoint);
            listOrderly.add(holdPoint);
        }

        Collections.sort(listOrderly, new SortByY()); // ordena a lista tendo em conta as ordenadas de cada ponto

        int reachMax = Integer.MIN_VALUE;
        for (int i = 0; i < c; i++) { // Calcula o maior reach que existe no conjunto de testes
            int r = Integer.parseInt(input.readLine());
            if (r > reachMax)
                reachMax = r;
            reachList.add(r);
        }

        ArrayList<holdPoint> holdPointBegin; // Lista com os holdPoints que podemos começar com

        double distance;
        holdPoint holdPoint2;
        for (int i = 0; i < listOrderly.size(); i++) { // Para cada ponto vai verificar as suas ligações e atribuir as respetivas arestas do grafo
            int count = 0;
            for (int j = i + 1; j < listOrderly.size() && count < 150; j++) {
                holdPoint2 = listOrderly.get(j);
                if (listOrderly.get(i) != holdPoint2) {
                    distance = distancia2d(listOrderly.get(i).getX(), listOrderly.get(i).getY(), holdPoint2.getX(),
                            holdPoint2.getY());
                    if (holdPoint2.getY() > listOrderly.get(i).getY() + reachMax)
                        break;
                    if (distance <= reachMax) {
                        g.addEdge(listOrderly.get(i), holdPoint2, distance);
                        count++;
                    }
                }
            }
        }
        for (int reach : reachList) {

            if (reach >= h) { // Se o reach for maior que a altura da parede significa que não é necessário agarra-se em nenhum holdPoint
                System.out.println(0);
            } else {

                holdPointBegin = beginNode(reach, listOrderly);

                boolean u = false;
                if (holdPointBegin.size() == 0) { // Se a lista estiver vazia significa que não podemos começar com nenhum nó
                    System.out.println("unreachable");
                    u = true;
                }

                if (!u) {
                    int aux;
                    aux = g.BFS(h, reach, holdPointBegin, listOrderly) + 1;
                    if (aux > n || aux <= 0) {
                        System.out.println("unreachable");
                    } else
                        System.out.println(aux);
                }
            }
        }
    }

    public enum Color {
        WHITE,
        GREY,
        BLACK
    }

    public static class holdPoint {
        public int x;
        public int y;
        public ArrayList<Aresta> l;
        public Color color;
        public int d;

        public holdPoint(int x, int y) {
            l = new ArrayList<>();
            this.x = x;
            this.y = y;
            this.color = Color.WHITE;
            this.d = Integer.MAX_VALUE;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public ArrayList<Aresta> getL() {
            return l;
        }
    }

    public static class Aresta {
        public holdPoint h;
        public double peso;

        public Aresta(holdPoint h, double peso) {
            this.h = h;
            this.peso = peso;
        }

        public holdPoint getH() {
            return h;
        }

        public double getPeso() {
            return peso;
        }
    }

    public static class Graph {
        int nodes; // Número de nós
        ArrayList<holdPoint> adjacents; // Lista de adjacência

        public Graph(int nodes) {
            this.nodes = nodes;
            adjacents = new ArrayList<>(nodes);
        }

        public void addNode(holdPoint h) {
            adjacents.add(h);
        }

        public void addEdge(holdPoint u, holdPoint v, double peso) {
            u.getL().add(new Aresta(v, peso));
            v.getL().add(new Aresta(u, peso));
        }

        public void removeQueue(ArrayList<holdPoint> listOrderly) {
            for (holdPoint holdPoint : listOrderly) {
                holdPoint.color = Color.WHITE;
                holdPoint.d = Integer.MAX_VALUE;
            }
        }

        public int BFS(int heigth, int reach, ArrayList<holdPoint> holdPointBegin, ArrayList<holdPoint> listOrderly) {
            holdPoint u;
            Queue<holdPoint> queue = new LinkedList<>();
            for (Main.holdPoint holdPoint : holdPointBegin) { // Coloca na queue todos os pontos em que podemos começar
                u = holdPoint;
                if (u.getY() + reach >= heigth)
                    return 0;
                u.color = Color.GREY;
                u.d = 0;
                queue.add(u);
            }

            while (!queue.isEmpty()) {
                u = queue.remove();
                for (Aresta a : u.getL()) {
                    holdPoint holdPointA = a.getH();
                    if (holdPointA.color == Color.WHITE && a.getPeso() <= reach) {
                        if (holdPointA.getY() + reach >= heigth) {
                            int x = u.d + 1;
                            u.d = Integer.MAX_VALUE;
                            u.color = Color.WHITE;
                            removeQueue(listOrderly);
                            return x;
                        }
                        holdPointA.color = Color.GREY;
                        holdPointA.d = u.d + 1;
                        queue.add(holdPointA);
                    }
                }
                u.color = Color.BLACK;
                u.d = Integer.MAX_VALUE;
            }
            removeQueue(listOrderly);
            return -1;
        }

    }

    static class SortByY implements Comparator<holdPoint> {
        @Override
        public int compare(holdPoint a, holdPoint b) {

            Integer yA = a.getY();
            Integer yB = b.getY();

            return yA - yB;

        }
    }
}



public class BigInt implements AstroInt {

    private String str;
    public DoubleLinkedList<Integer> dll = new DoubleLinkedList<>();
    public int negative = 0;



    public BigInt(DoubleLinkedList dll) {
        this.dll = dll;
    }

    public BigInt() {
    }

    public BigInt(String str) {
        this.str = str;
        int i = 0;
        char at = str.charAt(0);
        if (at == '-') {
            negative++;
            i = 1;
        }
        while (i < str.length()) {
            int x = Integer.parseInt(String.valueOf(str.charAt(i)));
            dll.add(x);
            i++;
        }
    }

    public DoubleLinkedList getdll() {
        return this.dll;
    } //getter

    public int getnegative() {
        return this.negative;
    }


    @Override
    public AstroInt add(AstroInt x) {
        String s = "";
        int bothNegative = negative + x.getnegative();
        int FirstNegative = negative;
        BigInt t = (BigInt)x;
        int xNegative = t.negative;
        DoubleLinkedList<Integer> maior1 = new DoubleLinkedList<>(); //criei lista para saber qual a maior lista
        int auxContas = 0;
        int menor = 0;
        int maior = 0;
        int i = 0;
        DoubleLinkedList<Integer> res = new DoubleLinkedList<>();  // lista que vai conter o resultado e depois vai passar a lista para o valor do resultado
        DoubleLinkedList<Integer> dl1 = x.getdll(); // lista do AstroInt recebido
        if (negative == 0 && x.getnegative() == 1) {
            BigInt y = (BigInt)x;
            y.negative = 0;

            BigInt res9 = (BigInt)sub(y);
            ((BigInt) x).negative = 1;
            return res9;
        } else if (negative == 1 && x.getnegative() == 0) {
            negative = 0;
            BigInt res11 = (BigInt)x.sub(this);
            negative = 1;
            return res11;
        } else {

            if (dll.size() - 1 > dl1.size() - 1) {
                menor = dl1.size();
                maior = dll.size();
                maior1 = dll;

            } else if (dl1.size() - 1 > dll.size() - 1) {
                menor = dll.size();
                maior = dl1.size();
                maior1 = dl1;
            } else {
                maior1 = dll;
                menor = dll.size();
            }
            for (i = 1; i <= menor; i++) {
                int y = dl1.get(dl1.size() - i);
                int z = dll.get(dll.size() - i);
                int res1 = y + z + auxContas;
                if (res1 > 9) {
                    res1 -= 10;
                    if (auxContas != 0) {
                        res.add(0, res1);
                    } else {
                        res.add(0, res1);
                    }
                    auxContas = 1;
                } else {
                    if (auxContas != 0) {
                        res.add(0, res1);
                        auxContas = 0;
                    } else {
                        res.add(0, res1);
                    }
                }
            }
            while (i <= maior1.size()) {
                if (auxContas != 0) {
                    if(maior1.get(maior1.size() - i) + 1 > 9){
                        auxContas = 1;
                        res.add(0,(maior1.get(maior1.size() - i) + 1)-10);
                    }else {
                        res.add(0, maior1.get(maior1.size() - i) + 1);
                        auxContas = 0;
                    }

                } else
                    res.add(0, maior1.get(maior1.size() - i));
                i++;
            }
            if (auxContas == 1) {
                res.add(0, 1);
            }


            for (int j = 0; j < res.size(); j++) {
                if (bothNegative == 2) {
                    int r = res.get(0);
                    s = s + -r;
                    bothNegative = 0;
                } else
                    s = s + res.get(j).toString();
            }


        }
        negative = FirstNegative;
        ((BigInt) x).negative = xNegative;
        BigInt res2 = new BigInt(s);
        return res2;
    }

    @Override
    public AstroInt sub(AstroInt x) {
        String s = "";
        int bothNegative = negative + x.getnegative();
        int FirstNegative = negative;
        BigInt t = (BigInt)x;
        int xNegative = t.negative;
        DoubleLinkedList<Integer> res = new DoubleLinkedList<>();
        DoubleLinkedList<Integer> dl1 = x.getdll();
        boolean iguais = false ;
        int auxContas = 0;
        int i = 0;

        if(negative == 1 && x.getnegative() == 0){

            negative = 0;
            BigInt soma = (BigInt)this.add(x);
            int f =soma.dll.get(0);
            for (int j = 0; j < soma.dll.size(); j++) {
               if(j == 0){
                   s = s + -f;
               }else
                    s = s + soma.dll.get(j).toString();
            }
            negative = 1;
            BigInt res5 = new BigInt(s);
            return res5;

        }else if( negative == 0 && x.getnegative() == 1){
            BigInt y = (BigInt) x;
            y.negative = 0;

            BigInt res6  = (BigInt)this.add(y);
            ((BigInt) x).negative = 1;
            return res6;

        }


            if (dll.size() - 1 > dl1.size() - 1) {
                for (i = 1; i <= dl1.size(); i++) {
                    int z = dll.get(dll.size() - i);
                    int y = dl1.get(dl1.size() - i);
                    int res1 = z - y;
                    if (res1 < 0) {
                        z += 10;
                        res1 = z - y;
                        if (res1 == 0 && auxContas != 0) {
                            res.add(0, 9);
                        } else
                            res.add(0, res1 - auxContas);
                        auxContas = 1;
                    } else {
                        if (res1 == 0 && auxContas == 0) {
                            res.add(0, 0);
                            auxContas = 0;
                        } else if (res1 == 0 && auxContas != 0) {
                            res.add(0, 9);
                            auxContas = 1;
                        } else {
                            res.add(0, res1 - auxContas);
                            auxContas = 0;
                        }
                    }
                }

                while (i <= dll.size()) {
                    if (dll.get(dll.size() - i) - auxContas < 0) {
                        res.add(0, 9);
                        auxContas = 1;
                    } else {
                        res.add(0, dll.get(dll.size() - i) - auxContas);
                        auxContas = 0;
                    }
                    i++;
                }
            } else if (dl1.size() - 1 > dll.size() - 1) {
                for (i = 1; i <= dll.size(); i++) {
                    int z = dl1.get(dl1.size() - i);
                    int y = dll.get(dll.size() - i);
                    int res1 = z - y;
                    if (res1 < 0) {
                        z += 10;
                        res1 = z - y;
                        if (res1 == 0 && auxContas != 0) {
                            res.add(0, 9);
                            auxContas = 0;
                        } else
                            res.add(0, res1 - auxContas);
                        auxContas = 1;
                    } else {
                        if (res1 == 0 && auxContas == 0) {
                            res.add(0, 0);
                            auxContas = 0;
                        } else if (res1 == 0 && auxContas != 0) {
                            res.add(0, 9);
                            auxContas = 0;
                        } else
                            res.add(0, res1 - auxContas);
                        auxContas = 0;
                    }
                }

                while (i <= dl1.size()) {
                    if (i + 1 > dl1.size() && dl1.get(dl1.size() - i) - auxContas == 0) {

                    } else {
                        res.add(0, dl1.get(dl1.size() - i) - auxContas);
                    }
                    auxContas = 0;
                    i++;
                }
                int buscar = res.get(0);
                res.set(0, -buscar);

            } else {
                int j = 0, value1 = 0, value2 = 0;
                DoubleLinkedList<Integer> maior = null;
                DoubleLinkedList<Integer> menor = null;
                do {
                    value1 = dll.get(j);
                    value2 = dl1.get(j);
                    if (value1 > value2) {
                        maior = dll;
                        menor = dl1;
                    } else if (value2 > value1){
                        maior = dl1;
                        menor = dll;
                    }else {
                        maior = dl1;
                        menor = dll;
                        iguais = true;
                    }
                    j++;
                } while (value1 == value2 && j < dll.size());


                for (i = 1; i <= dl1.size(); i++) {
                    int z = maior.get(maior.size() - i);
                    int y = menor.get(menor.size() - i);
                    int res1 = z - y;
                    if (res1 < 0) {
                        z += 10;
                        res1 = z - y;
                        if (res1 == 0 && i + 1 > dl1.size()) {

                        } else if (res1 == 0 && auxContas != 0) {
                            res.add(0, 9);
                            auxContas = 0;
                        } else res.add(0, res1 - auxContas);
                        auxContas = 1;
                    } else {
                        if (i  > dl1.size() && res1 == 0) {

                        } else if (res1 == 0 && auxContas == 0) {
                            res.add(0, 0);
                            auxContas = 0;
                        } else if (res1 == 0 && auxContas != 0) {
                            res.add(0, 9);
                            auxContas = 0;
                        } else
                            res.add(0, res1 - auxContas);
                        auxContas = 0;
                    }
                }

                if (maior == dl1 && !iguais  && x.getnegative() != 1) {
                    int buscar = res.get(0);
                    res.set(0, -buscar);
                }

            }

        for (int j = 0; j < res.size(); j++) {
            if (bothNegative == 2) {
                int r = res.get(0);
                s = s + -r;
                bothNegative = 0;
            } else
                s = s + res.get(j).toString();
        }
        negative = FirstNegative;
        ((BigInt) x).negative = xNegative;

        BigInt res2 = new BigInt(s);
        return res2;
    }

    public int  CasoPrimeiraConta(DoubleLinkedList<Integer> menor , DoubleLinkedList<Integer> maior , int i , int j , int auxContas , DoubleLinkedList<Integer> aux ){
        int res , contadorAux;
        res = menor.get(i-1) * maior.get(j-1) + auxContas;

        if (res > 9) {
            contadorAux = res / 10;
            res %= 10;
            aux.add(0, res);
            auxContas = contadorAux;

        } else {
            auxContas = 0;
            aux.add(0, res);
        }

        if (j == 1 && auxContas != 0) {
            aux.add(0, auxContas);
        }
        return auxContas;
    }

    public int CasoSegundaMaisConta(DoubleLinkedList<Integer> menor , DoubleLinkedList<Integer> maior , int i , int j , int auxContas , int auxiliarParaAux, DoubleLinkedList<Integer> aux ){
        int res;
        res = menor.get(i-1) * maior.get(j-1) +  aux.get(aux.size()-auxiliarParaAux -1) + auxContas  ;

        if (res > 9) {
            auxContas = res / 10;
            res %= 10;
            if(j == 1){
                aux.add(0,auxContas);
            }
            aux.set(aux.size()- auxiliarParaAux -1 ,res);
        } else {
            auxContas = res/10;
            res= res %10;
            aux.set(aux.size() - auxiliarParaAux -1 , res);
        }
        return auxContas;
    }

    @Override
    public AstroInt mult(AstroInt x) {
        String s = "";
        DoubleLinkedList<Integer> dl1 = x.getdll();
        DoubleLinkedList<Integer> menor;
        DoubleLinkedList<Integer> maior;
        DoubleLinkedList<Integer> auxiliar = new DoubleLinkedList<>();
        int FirstNegative = negative;
        BigInt t = (BigInt)x;
        int xNegative = t.negative;
        int res = 0;
        int auxContas = 0;
        int auxiliarParaAux = 0;
        int contador = 0;
        int contadorAux = 0;
        if (dll.size()  > dl1.size() ) {
            menor = dl1;
            maior = dll;
        } else {
            menor = dll;
            maior = dl1;
        }

        for (int i = menor.size(); i > 0 ; i--) {
            auxiliarParaAux = contador ;
            auxContas = 0;

            for (int j = maior.size(); j > 0  ; j--) {
                if (i == menor.size()) { // primeira conta de mult

                    auxContas = CasoPrimeiraConta(menor,maior,i,j,auxContas,auxiliar); // decidi criar este método para facilitar a leitura

                } else {
                    if (auxiliar.size() - auxiliarParaAux  > 0) {
                        auxContas = CasoSegundaMaisConta(menor,maior,i,j,auxContas,auxiliarParaAux,auxiliar); // decidi criar este método para facilitar a leitura

                    } else {
                        res = menor.get(i-1) * maior.get(j-1) + auxContas  ;
                            int auxiliar5 = res % 10;
                        auxiliar.add(0, auxiliar5);
                            res /= 10;
                        auxiliar.add(0, res);
                    }


                }

                auxiliarParaAux++;
            }
            contador++;
        }
        for (int j = 0; j < auxiliar.size(); j++) {
            if (auxiliar.get(0) == 0) {
                if (j == 0) {

                } else {
                    if (negative == 1 && x.getnegative() == 0) {
                        int r = auxiliar.get(0);
                        s = s + -r;
                        negative = 0;

                        BigInt m = (BigInt) x;
                        m.negative = 0;
                    }else if(negative == 0 && x.getnegative() == 1){
                        int r = auxiliar.get(0);
                        s = s + -r;
                        negative = 0;

                        BigInt m = (BigInt) x;
                        m.negative = 0;
                    }



                    else
                        s = s + auxiliar.get(j).toString();


                }


            } else {
                if (negative == 1 && x.getnegative() == 0) {
                    int r = auxiliar.get(0);
                    s = s + -r;
                    negative = 0;

                    BigInt m = (BigInt) x;
                    m.negative = 0;
                } else if(negative == 0 && x.getnegative() == 1){
                    int r = auxiliar.get(0);
                    s = s + -r;
                    negative = 0;

                    BigInt m = (BigInt) x;
                    m.negative = 0;
                }





              else
                    s = s + auxiliar.get(j).toString();


            }


        }
        negative = FirstNegative;
        ((BigInt) x).negative = xNegative;
        BigInt res5 = new BigInt(s);
        return res5;
    }



    @Override
    public AstroInt div(AstroInt x) {
        String s = "";
        int bothNegative  = negative + x.getnegative();
        int FirstNegative = negative;
        BigInt t = (BigInt)x;
        int xNegative = t.negative;
        BigInt Contador1 = new BigInt("0");
        BigInt valorASomar = new BigInt("1");
        BigInt valorSaltos = new BigInt("10000000");
        BigInt i = new BigInt("1");
        BigInt res = new BigInt();
        BigInt valorasomar2 = new BigInt("2");
        DoubleLinkedList<Integer> ListThis = this.getdll();
        DoubleLinkedList<Integer> ListX = x.getdll();
        if(ListX.size() > ListThis.size()){
             Contador1 = valorASomar ;
        }else if (!maior(res,this)) {
            Contador1 = valorasomar2;
        }else{
            do {
                res = (BigInt) i.mult(x);
                Contador1 = (BigInt)Contador1.add(valorASomar);
                i = (BigInt)i.add(valorASomar);
            } while (maior(res, this));

        }
        Contador1 = (BigInt)Contador1.sub(valorASomar);
        for (int j = 0; j < Contador1.dll.size(); j++) {
            if (bothNegative == 1) {
                int r = Contador1.dll.get(0);
                s = s + -r;
                negative = 0;
                BigInt m = (BigInt) x;
                m.negative = 0;
                bothNegative = 0;
            }else
                s = s + Contador1.dll.get(j).toString();
            negative = FirstNegative;
            ((BigInt) x).negative = xNegative;
            if(j+1 >= Contador1.dll.size()){
                BigInt resultadoFinal = new BigInt(s);
                return resultadoFinal;
            }
        }
        negative = FirstNegative;
        ((BigInt) x).negative = xNegative;
        return Contador1;
    }

    @Override
    public AstroInt mod(AstroInt x) {
        String s = "" ;
        if(x.getnegative() == 1){
            return null;
        }
        int p  = negative;
        int o = 0 ;
        negative = 0;
        int j = 0;
        BigInt resultadoDivisao = (BigInt)this.div(x);
        BigInt multiplicacao = (BigInt)resultadoDivisao.mult(x);
        BigInt resultadoFinal = (BigInt)this.sub(multiplicacao);
        if (maior(this,x)){
            return this;
        }
        if(p == 1) {
            for (j = 0; resultadoFinal.dll.get(j) == 0 && j < resultadoFinal.dll.size(); j++) {
                if (resultadoFinal.dll.get(j) == 0 && s.equals("")) {

                }
            }
            o = j;
            while (j < resultadoFinal.dll.size()) {

                  if(j == o) {
                      int r = resultadoFinal.dll.get(j);
                      s = s + -r;
                  }
                    else
                    s = s + resultadoFinal.dll.get(j).toString();
                    j++;
            }
            BigInt res10 = new BigInt(s);
            return res10;
        }
        return resultadoFinal;

    }

    public boolean maior(AstroInt resultado, AstroInt whatWeWant){ // é falso quando já ultrapasssamos o valor que queremos
         DoubleLinkedList<Integer> resultado1 = resultado.getdll();
         DoubleLinkedList<Integer> resultado2 = whatWeWant.getdll();
         int i = 0;
         do{
             if(resultado1.size() > resultado2.size()){
                 return false;
             }else if(resultado2.size() > resultado1.size()){
                 return true;
             }else{
                 if(resultado1.get(i) > resultado2.get(i)){
                     return false;
                 }else if(resultado2.get(i) > resultado1.get(i)){
                     return true;
                 }
             }
             i++;
         }while(i < resultado1.size());

          return true;
    }

    public boolean igual(AstroInt x , AstroInt ValorQueQueremos){
           DoubleLinkedList<Integer> resultado1 = x.getdll();
           DoubleLinkedList<Integer> resultado2 = ValorQueQueremos.getdll();
           int i = 0;

           if(resultado1.size() > resultado2.size()){
               return false;
           }

           if(resultado2.size() > resultado1.size() ){
               return false;
           }

           do{
               if(!resultado1.get(i).equals(resultado2.get(i)))
                   return false;
               i++;

           }while(i < resultado1.size());

           return true;
    }




    @Override
    public String toString() { //mostra ou o resultado da operação feita ou entao o valor da string inicial caso nao tenha sido efetuada nenhuma operação
        return str;
    }
}

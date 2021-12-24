public class Compartimento {

    public int compartimento;
    public String produto;
    public double precoUni;
    public int quantidade;

    public Compartimento(){}

    public Compartimento(int quantidade,String produto,double precoUni,int compartimento){
        this.quantidade = quantidade;
        this.produto = produto;
        this.precoUni = precoUni;
        this.compartimento = compartimento;
    }

    public double getPrecoUni() {
        return precoUni;
    }

    public int getCompartimento() {
        return compartimento;
    }

    public int getQuantidade() {
        return quantidade;
    }

    public String getProduto() {
        return produto;
    }

    public void setCompartimento(int compartimento) {
        this.compartimento = compartimento;
    }

    public void setPrecoUni(double precoUni) {
        this.precoUni = precoUni;
    }

    public void setProduto(String produto) {
        this.produto = produto;
    }

    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }


}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int baixo(int grelha[10][10],int sz)
{
int col=0,lin=0,i=0,combi=0;
    while(col<sz)
    {
        while(i<sz)
        {
            while(lin+1<sz)
            {
                if( grelha[lin+1][col]==0)
                {

                    grelha[lin+1][col]=grelha[lin][col];
                    grelha[lin][col]=0;
                }
                lin++;
            }
            i++;
            lin=0;

        }
        col++;
        i=0;
}

    col=0;
    lin=sz-1;
    while(col<sz)
    {
        while(lin>=0)
        {

            if(grelha[lin][col]==grelha[lin-1][col] )
            {

                grelha[lin][col] *=2;
                grelha[lin-1][col]=0;
                combi++;
            }
            lin--;
        }
        col++;
        lin=sz-1;
    }
    col=0;
    lin=0;
    i=0;
    while(col<sz)
    {
        while(i<sz)
        {
            while(lin+1<sz)
            {
                if(grelha[lin+1][col]==0)
                {

                    grelha[lin+1][col]=grelha[lin][col];
                    grelha[lin][col]=0;
                }
                lin++;
            }
            i++;
            lin=0;
        }
        col++;
        i=0;
    }

    return combi;
}



int cima(int grelha[10][10],int sz)
{
    int col=0,lin=0,i=0,combi=0;
    while(col<sz)
    {
        while(i<sz)
        {
            while(lin+1<sz)
            {
                if(grelha[lin][col]==0)
                {

                    grelha[lin][col]=grelha[lin+1][col];
                    grelha[lin+1][col]=0;


                }
                lin++;
            }
            i++;
            lin=0;
        }
        col++;
        i=0;

    }
    lin=0;
    col=0;
    while(col<sz)
    {
        while(lin+1<sz)
        {

            if(grelha[lin][col]==grelha[lin+1][col] && grelha[lin][col]!=0)
            {

                grelha[lin][col] *=2;
                grelha[lin+1][col]=0;
                combi++;

            }
            lin++;
        }
        col++;
        lin=0;
    }
    i=0;
    col=0;
    lin=0;
    while(col<sz)
    {
        while(i<sz)
        {
            while(lin+1<sz)
            {
                if(grelha[lin][col]==0)
                {

                    grelha[lin][col]=grelha[lin+1][col];
                    grelha[lin+1][col]=0;


                }
                lin++;
            }
            i++;
            lin=0;
        }
        col++;
        i=0;

    }
    return combi;
}



int direita(int grelha[10][10],int sz)
{
    int col=sz-1,lin=0,i=0,combi=0;
    i=0;
    col=0;
    lin=0;
    while(lin<sz)
    {
        while(i<sz)
        {
            while(col+1<sz)
            {
                if(grelha[lin][col+1]==0)
                {
                    grelha[lin][col+1]=grelha[lin][col];
                    grelha[lin][col]=0;

                }
                col++;

        }
        i++;
            col=0;

    }
    lin++;
        i=0;
    }
    lin=0;
    col=sz-1;
    while(lin<sz)
    {
        while(col>=0)
        {
            if(grelha[lin][col]==grelha[lin][col-1] && grelha[lin][col]!=0)
            {
                grelha[lin][col]*=2;
                grelha[lin][col-1]=0;
                combi++;
            }
            col--;
        }
        lin++;
        col=sz-1;
    }
    i=0;
    col=0;
    lin=0;
    while(lin<sz)
    {
        while(i<sz)
        {
            while(col+1<sz)
            {
                if(grelha[lin][col+1]==0)
                {
                    grelha[lin][col+1]=grelha[lin][col];
                    grelha[lin][col]=0;

                }
                col++;
            }
            i++;
            col=0;
        }
        col=0;
        lin++;
        i=0;

    }

    return combi;

}




int esquerda(int grelha[10][10],int sz)
{

    int col=0,lin=0,i=0,combi=0;
    i=0;
    col=0;
    lin=0;
    while(lin<sz)
    {
        while(i<sz)
        {
            while(col<sz-1)
            {
                if(grelha[lin][col]==0)
                {

                    grelha[lin][col]=grelha[lin][col+1];
                    grelha[lin][col+1]=0;

                }
                col++;
            }
            i++;
            col=0;
        }
        lin++;
        i=0;

    }
    lin=0;
    col=0;
    while(lin<sz)
    {
        while(col<sz)
        {
            if(grelha[lin][col]==grelha[lin][col+1] && grelha[lin][col]!=0)
            {

                grelha[lin][col]*=2;
                grelha[lin][col+1]=0;
                combi++;

            }
            col++;
        }
        lin++;
        col=0;

    }
    i=0;
    col=0;
    lin=0;
    while(lin<sz)
    {
        while(i<sz)
        {
            while(col<sz-1)
            {
                if(grelha[lin][col]==0)
                {

                    grelha[lin][col]=grelha[lin][col+1];
                    grelha[lin][col+1]=0;

                }
                col++;
            }
            i++;
            col=0;
        }
        lin++;
        i=0;

    }
    return combi;
}


int fim_jogo(int grelha[10][10],int sz){
int lin=0,col=0,u=0;
while(lin<sz){
    while(col<sz){
        if(grelha[lin][col]==0){
            u++;
        }
        col++;
    }
    lin++;
    col=0;
}
    lin=0;
    col=0;
    if(u==0){
    while(lin<sz){
        while(col<sz){
            if(lin==0 && col==0){
                if(grelha[lin][col]==grelha[lin][col+1] || grelha[lin][col]==grelha[lin+1][col]){
                    u++;
                }
                }else if(lin==0 && col==sz-1){
                if(grelha[lin][col]==grelha[lin+1][col] || grelha[lin][col]==grelha[lin][col-1]){
                    u++;
                }
                }else if(lin==sz-1 && col==0){
                if(grelha[lin][col]==grelha[lin-1][col] || grelha[lin][col]==grelha[lin][col+1]){
                    u++;
                }
                }else if(lin==sz-1 && col==sz-1){
                if(grelha[lin][col]==grelha[lin][col-1] || grelha[lin][col]==grelha[lin-1][col]){
                    u++;
                }
                }else{
                  if(grelha[lin][col]==grelha[lin][col-1] || grelha[lin][col]==grelha[lin][col+1] || grelha[lin][col]==grelha[lin+1][col]  || grelha[lin][col]==grelha[lin-1][col]){
                    u++;
                  }
                }
                col++;
            }
            lin++;
            col=0;
        }
        if(u==0){
            return -1;
        }

    }
    return 0;


}



void mostrar(int grelha[10][10],int sz)
{
    int col=0,lin=0,i,j,ran=1,u=0;
    srand(time(0));

    i=rand() %sz;
    j=rand() %sz;
    while(grelha[i][j]!=0 && u<sz*sz)
    {
        i=rand() %sz;
        j=rand() %sz;
        u++;

    }
    while(ran!=2 && ran!=4)
    {
        ran=rand() %5;
    }if(u!=sz*sz){
    grelha[i][j]=ran;
    }
    while(lin<sz)
    {
        while(col<sz)
        {

            if(grelha[lin][col]==0)
            {
                printf("-   ");
            }
            else if(grelha[lin][col]>99){
                    printf("%d ",grelha[lin][col]);

            }
            else if(grelha[lin][col]>9)
                {
                    printf("%d  ",grelha[lin][col]);

                }
                else
                {
                    printf("%d   ",grelha[lin][col]);          //u para ver se a grelha esta totalmente preenchida

                }
            col++;
            if(col==sz)
            {
                printf("\n");
            }
        }
        lin++;
        col=0;
    }

}




int jogada(int grelha[10][10],int sz,char sentido[2]){
int combinadas=0,combi,j=0,i=0,u;
while(j<strlen(sentido)){
if(sentido[j]=='b' || sentido[j]=='B'){                          //jogo nao termina quando nao existem mais opcoes
    combi=baixo(grelha,sz);
    combinadas+=combi;
    mostrar(grelha,sz);
    u=fim_jogo(grelha,sz);
}else if(sentido[j]=='c' || sentido[j]=='C'){
     combi=cima(grelha,sz);
     combinadas+=combi;
     mostrar(grelha,sz);
     u=fim_jogo(grelha,sz);
}else if(sentido[j]=='d' || sentido[j]=='D'){
    combi=direita(grelha,sz);
    combinadas+=combi;
    mostrar(grelha,sz);

    u=fim_jogo(grelha,sz);
}else if(sentido[j]=='e' || sentido[j]=='E'){
    combi=esquerda(grelha,sz);
    combinadas+=combi;
    mostrar(grelha,sz);
    u=fim_jogo(grelha,sz);
}else if(sentido[j]=='f' || sentido[j]=='F'){
    j=strlen(sentido);
    return -1;

}
if(u==-1){
    return -1;
}

j++;

}
return combinadas;
}



int main()
{
    int i,sz,lin=0,col=0,ran,grelha[10][10],j,u,r,combi,combinadas=0;
    char sentido[10];
    printf("Insira a dimensao do tabela: ");
    scanf("%d",&sz);
    while(sz>10 || sz<0)
    {
        printf("O valor maximo e 10\n");
        printf("Insira um novo valor: ");
        scanf("%d",&sz);
    }
    ran=1;
    srand(time(0));
    printf("\nB-baixo\nC-cima\nD-direita\nE-esquerda\n\n");
    i=rand() %sz;
    j=rand() %sz;
    while(ran!=2 && ran!=4)
    {
        ran=rand() %5;
    }
    grelha[i][j]=ran;
    ran=1;
    u=i;
    r=j;
    while(u==i && r==j)
    {
        u=rand() %sz;
        r=rand() %sz;
    }
    while(ran!=2 && ran!=4)
    {
        ran=rand() %5;
    }
    grelha[u][r]=ran;

    while(lin<sz)
    {
        while(col<sz)
        {
            if(lin==i && col==j)
            {
                grelha[lin][col]=grelha[i][j];
            }
            else if(lin==u && col==r)
            {
                grelha[lin][col]=grelha[u][r];
            }
            else
            {
                grelha[lin][col]=0;
            }
            if(grelha[lin][col]==0)
            {
                printf("-   ");
            }
            else
            {
                printf("%d   ",grelha[lin][col]);
            }
            col++;
            if(col==sz)
            {
                printf("\n");
            }
        }
        lin++;
        col=0;
    }
    scanf("%c",sentido);
    while(combi>=0){
    combi=jogada(grelha,sz,sentido);
    if(combi<0){
        printf("FIM DO JOGO\npecas combinadas: %d\n",combinadas);
        return 0;
    }
    else if(combi>=0){
    combinadas+=combi;
    scanf("%c",sentido);
    }
    }
    return 0;
    }



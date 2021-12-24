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
        while(lin>0)
        {

            if(grelha[lin][col]==grelha[lin-1][col] && grelha[lin][col]!=0)
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
        while(col+1<sz)
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

int main(){
    int sz,lin=0,col=0,grelha[10][10],i=0,num[2049],j,combi=0,combinadas=0;
    char sentido[200],ficheiro[20];
 FILE *file;
 printf("Insira o nome do ficheiro:");
 scanf("%s",ficheiro);

 file=fopen(ficheiro,"r");
 if(file==NULL){
        printf("Nao foi possivel ler o ficheiro.");
    return 0;
    }
 fscanf(file,"%d\n",&sz);
 while(lin<sz){
        while(col<sz){
    fscanf(file,"%d",&grelha[lin][col]);
    col++;
    if(col==sz){
        fscanf(file,"\n");
    }
        }
lin++;
col=0;
 }
 j=0;
 i=0;
 fgets(sentido,200,file);
 while(j<strlen(sentido)){
    if(sentido[i]=='D'){

            combi=direita(grelha,sz);
combinadas+=combi;
    }else if(sentido[i]=='C'){
            combi=cima(grelha,sz);
combinadas+=combi;
    }else if(sentido[i]=='B'){

            combi=baixo(grelha,sz);
combinadas+=combi;
    }else if(sentido[i]=='E'){

            combi=esquerda(grelha,sz);
combinadas+=combi;
    }
    i++;
    j++;

 }
 lin=0;
 col=0;
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

lin=0;
col=0;
i=2;          //para i ir alternado entre multiplos de dois ate 2048
while(lin<sz){                 //contagem
    while(col<sz){
            while(i<=2048 && grelha[lin][col]!=0){
        if(grelha[lin][col]==i ){
            num[i]+=1;
            i=2049;
        }else{
           i*=2;
             }
            }
            col++;
            i=2;
    }
    lin++;
    col=0;
}
printf("\ncombinacoes: %d",combinadas);
printf("\ncontagem: %d %d %d %d",num[2],num[4],num[8],num[16]);
 fclose(file);
 return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int topo;
int pilha[50];

void construtor()
{
    topo=0;
}

bool vazia()
{
    if(topo==0)
    {
        return true;    //se a pilha estiver vazia retorna true senao retorna false
    }
    return false;

}

bool cheia()
{
    if(topo==49)    // se estiver cheia retorna true senao retorna false
    {
        return true;
    }
    return false;

}

bool push(int num)
{
    if(cheia())
    {
        return false;  //nao consegue colocar mais nada
    }
    topo++;
    pilha[topo]=num;

    return true;
}

bool pop(int *num)
{
    if(vazia())
    {
        return false; //nao consegue ir buscar nada pilha vazia
    }
    *num=pilha[topo];
    topo--;
    return true;


}

void soma()     //realiza a soma entre dois valores
{
    int num,num1;
    pop(&num);
    pop(&num1);
    push(num1+num);

}

void sub()     ////realiza a subtraçâo entre dois valores
{
    int num,num1;
    pop(&num);
    pop(&num1);
    push(num1-num);
}

void multi()  //realiza a multiplicaçao entre dois valores
{
    int num,num1;
    pop(&num);
    pop(&num1);
    push(num1*num);
}

void divi()  //realiza a divisâo entre dois valores
{
    int num,num1;
    pop(&num);
    pop(&num1);
    push(num1/num);

}

void neg()   //realiza o simetrico de um valor do topo da pilha
{
    int num;
    pop(&num);
    push(-num);

}

void swap() // troca o valor do topo da pilha com o abaixo do topo
{
    int num,num1;
    pop(&num);
    pop(&num1);
    push(num);
    push(num1);
}

void dup()   //duplica o valor do topo da pilha
{
    int num;
    pop(&num);
    push(num);
    push(num);
}

void drop() //elimina o valor do topo da pilha
{
    int num;
    pop(&num);
}

void clear()  //elimina tudo o que esteja na pilha
{
    int num;
    while(pop(&num))
    {
        pop(&num);

    }
}
void raiz()  // realiza a raiz de um valor
{
    int num;
    pop(&num);
    push(sqrt(num));

}

int tamanho()  //retorna o tamanho de valores da pilha
{
    return topo;
}

void cabecalho()
{
    printf("*************************************************\n");
    printf("*** RPN - Reverse Polish Notation Calculator  ***\n");
    printf("*** Rafael Silva (45813) e Pedro Anjos (45558)***\n");
    printf("***            ASC1 2019/2020                 ***\n");
    printf("*************************************************\n");
    printf("type help for available commands\n\n");
}

void help()
{
    printf("\n + --> somar\n");
    printf(" - --> subtrair\n");
    printf(" * --> multiplicação\n");
    printf(" / --> dividir\n");
    printf(" neg --> simétrico\n");
    printf(" dup --> duplica o topo da pilha\n");
    printf(" drop --> Elimina um operando do topo da pilha");
    printf(" sqr --> calcula a raiz quadrada\n");
    printf(" swap--> troca os operadores do topo da pilha\n\n");

}

void second_main()
{
    int num,i=0,count;
    char s[100];
    while(strcmp(s,"off")!=0)
    {
        printf("-> ");
        scanf("%s",s);
        if(strcmp(s,"+")==0)        //VER QUANDO METER OFF E VER HELP
        {
            soma();
        }
        else if(strcmp(s,"-")==0)
        {
            sub();
        }
        else if(strcmp(s,"*")==0)
        {
            multi();
        }
        else if(strcmp(s,"/")==0)
        {
            divi();
        }
        else if(strcmp(s,"neg")==0)
        {
            neg();
        }
        else if(strcmp(s,"swap")==0)
        {
            swap();
        }
        else if(strcmp(s,"dup")==0)
        {
            dup();
        }
        else if(strcmp(s,"drop")==0)
        {
            drop();
        }
        else if(strcmp(s,"clear")==0)
        {
            clear();
        }
        else if(strcmp(s,"sqrt")==0)
        {
            raiz();
        }
        else if(strcmp(s,"help")==0)
        {
            help();
        }
        else
        {
            num=atoi(s);
            push(num);
        }

        if(strcmp(s,"off")!=0 && strcmp(s,"help")!=0)
        {
            printf("stack:\n");
            if(tamanho()==0)

            {
                printf("(empty)\n");
            }
        }
        count=1;
        while(count<tamanho()+1 && strcmp(s,"off")!=0 && strcmp(s,"help")!=0)
        {
            printf("%d\n",pilha[count]);
            count++;
        }
        printf("\n");
    }
    printf("\nBye!");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    cabecalho();
    printf("stack:\n");
    printf("(empty)\n\n");
    second_main();
}

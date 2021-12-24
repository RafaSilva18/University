#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define COLUMN 10
#define LINE 5
#define RR 0
#define VRR 1
#define ALGORITMO VRR


struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
            sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
            queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

bool findInt(int num,struct Queue* queue)
{
    for(int i=0;i<LINE;i++) {
        if (num+1 == queue->array[queue->front+i]){
            return true;
        }
    }
    return false;
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

// Function to get rear of queue
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}











void output(int linha,char assign[]){
    if(linha == 0 )
        printf("       %s",assign);
    else
        printf("     %s",assign);
}

bool verificaColuna(int programa[][COLUMN],int coluna){
    int contador = 0;
    for(int i = 0;i<LINE;i++){
        if(programa[i][coluna] == 0){
            contador++;
        }
    }
    if(contador == LINE) return true;
    return false;
}

bool terminouProcesso(int programas [][COLUMN], int coluna,int linha){
    if( coluna + 1 < COLUMN && programas[linha][coluna+1] == 0 || coluna + 1 == COLUMN){
        return true;
    }
    return false;
}




int main()
{
    int programas[5][10] = {

            {0, 3, 1, 2, 2, 4, 1, 1, 1, 1 } ,

            {1, 2, 4, 2, 4, 2, 0, 0, 0, 0 } ,

            {3, 1, 6, 1, 6, 1, 6, 1, 0, 0 } ,

            {3, 6, 1, 6, 1, 6, 1, 6, 0, 0 } ,


            {5, 9, 1, 9, 0, 0, 0, 0, 0, 0 }

    };
    struct Queue* ready = createQueue(30);
    struct Queue* blocked = createQueue(30);
    struct Queue* readyAux = createQueue(30);
    struct Queue* new = createQueue(30);
    struct Queue* exit = createQueue(30);
    int linha = 0;
    int coluna = 0;
    int instantes = 2;
    int quantum = 3;
    int auxquantum = 0,auxTerminar = 0;
    int aux1 = -1 ,aux2 = -1,aux5 = -1;
    char n[] = "NEW";
    char r[] = "RDY";
    char b[] = "BLO";
    char rn[] = "RUN";
    char a[] = "AUX";
    bool run = false , dontRun = false , auxReadyAux = false, stillRunning = false;
    bool sameTime = false , alreadyDequeue = false;
    bool terminarPrograma = false;
    bool auxterminar = false;

    printf("instante |");
    for(int i  = 1;i < LINE + 1 ;i++) {
        printf(" proc%d |",i);
    }
    printf("\n");
    printf("   1");


    while(linha<LINE){
        if(programas[linha][coluna] == 0) {
            enqueue(ready, linha+1);
            output(linha,n);
        }else{
            enqueue(new,linha+1);
            output(linha,"---");
        }

        linha++;
    }
    printf("\n");

    for(coluna = 0;coluna<=COLUMN && !auxterminar;coluna++) {
        printf("   %d", instantes);
        instantes++;
        for (linha = 0; linha< LINE; linha++){
            if(!isEmpty(ready) && front(ready) == linha + 1 && !run || (!isEmpty(readyAux) && front(readyAux) == linha + 1 && !run && !stillRunning)){
                if(front(ready) == linha + 1){
                    for(int x = linha+1;x < LINE;x++) {
                        if(!isEmpty(readyAux) && front(readyAux) == x + 1){
                            output(linha,r);
                            dontRun = true;
                        }
                    }
                }
                if(!dontRun) {
                    run = true;
                    stillRunning = true;
                    if(front(readyAux) == linha + 1){
                        output(front(readyAux)-1,rn);
                        stillRunning = false;
                    }
                    else
                       output(front(ready)-1,rn);
                    int aux = coluna;
                    auxquantum++;
                    while (programas[linha][coluna] == 0) {
                        coluna++;
                    }
                    programas[linha][coluna]--;
                    if (auxquantum == quantum && programas[linha][coluna] != 0) {
                        for (int x = linha + 1; x < LINE; x++) {
                            int aux3 = aux;
                            if (!isEmpty(blocked) && front(blocked) == x + 1) {
                                while (programas[x][aux3] == 0) {
                                    aux3++;
                                }

                                if (programas[x][aux3] - 1 == 0 && !terminouProcesso(programas, aux3, x)) {
                                    sameTime = true;
                                    aux5 = linha;
                                }
                            }
                        }
                        if (!sameTime) {
                            stillRunning = false;
                            if(front(readyAux) == linha + 1)
                                enqueue(ready, dequeue(readyAux));
                            else
                                enqueue(ready,dequeue(ready));
                            alreadyDequeue = true;
                        }
                        auxquantum = 0;
                        if(!alreadyDequeue)
                            aux1 = coluna;
                        if(front(readyAux) == linha + 1)
                            auxReadyAux = true;
                    }
                    if (programas[linha][coluna] == 0) {
                        if (!terminouProcesso(programas, coluna, linha)) {
                            enqueue(blocked, linha + 1);

                        } else {
                            enqueue(exit, linha + 1);

                        }
                        stillRunning = false;
                        auxquantum = 0;
                        if(front(readyAux) == linha + 1)
                            auxReadyAux = true;
                        aux1 = coluna;
                    }
                    coluna = aux;
                }
                dontRun = false;

            } else if (!isEmpty(new) && front(new) == linha + 1 && programas[linha][coluna]-1 == 0) {
                    programas[linha][coluna]--;
                if (programas[linha][coluna] == 0) {
                    enqueue(ready, dequeue(new));
                    output(linha, n);
                }
            }else if(findInt(linha, ready)) {
                output(linha, r);
            }else if(findInt(linha,readyAux)){
                output(linha,a);
            }else if (!isEmpty(blocked) && front(blocked) == linha + 1) {
                    output(front(blocked)-1,b);
                    int aux = coluna;
                    while (programas[linha][coluna] == 0) {
                        coluna++;
                    }
                    programas[linha][coluna]--;
                    if (programas[linha][coluna] == 0) {
                        if(!terminouProcesso(programas,coluna,linha)) {
                            if(ALGORITMO == RR) {
                                enqueue(ready, linha + 1);
                            }else{
                                enqueue(readyAux,linha + 1);
                            }
                        }
                        aux2 = coluna;

                    }
                    coluna = aux;

            }else if(findInt(linha,blocked)){
                output(linha,b);
            }else if(findInt(linha,exit)){
                output(linha,"EXT");
                dequeue(exit);
            }else{
                    if(!terminouProcesso(programas,coluna,linha)){
                        programas[linha][coluna]--;
                    }
                    if(auxTerminar == LINE - 1){
                        auxterminar = true;
                    }
                    output(linha,"---");
                    auxTerminar++;
            }
        }
        run = false;
        auxTerminar = 0;
        alreadyDequeue = false;
        if(sameTime){
            dequeue(ready);
            enqueue(ready,aux5+1);
            sameTime = false;
            stillRunning = false;
        }
        for(linha = 0;aux1 != -1 && linha<LINE;linha++){
            if(programas[linha][aux1] == 0) {
                if(!auxReadyAux && front(ready) == linha + 1) {
                    dequeue(ready);
                    break;
                }else if(auxReadyAux && front(readyAux) == linha + 1){
                    dequeue(readyAux);
                    auxReadyAux = false;
                    break;
                }
            }
        }

        for(linha = 0;aux2 != -1 && linha<LINE;linha++){
            if(programas[linha][aux2]== 0 && front(blocked)== linha+1){
                dequeue(blocked);
                break;
            }
        }
        aux1 = -1;
        aux2 = -1;
        auxReadyAux = false;
        if(!verificaColuna(programas,coluna) && !auxterminar){
            coluna--;
        }else if(coluna + 1 == COLUMN && !terminarPrograma && !auxterminar) {
            coluna--;
            terminarPrograma = true;
        }
        printf("\n");

    }
    return 0;
}


































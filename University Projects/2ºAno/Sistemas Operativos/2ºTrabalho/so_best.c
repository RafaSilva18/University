#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

#include <stdbool.h>

#include <string.h>


#define QUANTUM 3





struct Queue {

    int front, rear, size;

    unsigned capacity;

    int* array;

};





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





int isFull(struct Queue* queue)

{

    return (queue->size == queue->capacity);

}

int isEmpty(struct Queue* queue)

{

    return (queue->size == 0);

}

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

void enqueue(struct Queue* queue, int item)

{

    if (isFull(queue))

        return;

    queue->rear = (queue->rear + 1)

                  % queue->capacity;

    queue->array[queue->rear] = item;

    queue->size = queue->size + 1;

}




bool findInt(int num,struct Queue* queue,int numeroProcessos)

{

    for(int i=0;i<numeroProcessos;i++) {

        if (num+1 == queue->array[queue->front+i]){

            return true;

        }

    }

    return false;

}

void retira(int linha,struct  Queue* queue){
    for(int i=0;i < queue->size;i++){
        if(linha + 1 != queue->array[queue->front]){
            enqueue(queue, dequeue(queue));
        }else{
            dequeue(queue);
        }
    }
}

int front(struct Queue* queue)

{

    if (isEmpty(queue))

        return INT_MIN;

    return queue->array[queue->front];

}





int rear(struct Queue* queue)

{

    if (isEmpty(queue))

        return INT_MIN;

    return queue->array[queue->rear];

}


void Output(int newAux [] , int exitAux[] ,int readyAux[],int runAux[], int blockedAux[], int instante, int st, int countReady,int countRun,int countBlocked,int countNew,int countExit){
    int aux = 0;
    char mensagem[200];
    bzero(mensagem,200);
    if(instante == 0){
        strcat(mensagem," T  | stdout   | NEW      | EXIT     | READY                                   | RUN  |  BLOCKED");
    }else{
        char auxiliar[sizeof (int)];
        snprintf(auxiliar,sizeof (int),"%d",instante);
        if(instante < 10) {
            strcat(mensagem,"0");
            strcat(mensagem,auxiliar);
            strcat(mensagem,"  |    ");
        }else{
            strcat(mensagem,auxiliar);
            strcat(mensagem,"  |    ");
        }

        if(st != -1){
            bzero(auxiliar,sizeof (int));
            snprintf(auxiliar,sizeof (int),"%d",st);
            if(st/10 == 0) {
                strcat(mensagem," ");
                strcat(mensagem,auxiliar);
                strcat(mensagem,"    | ");
            }else if(st/100 == 0) {
                strcat(mensagem," ");
                strcat(mensagem,auxiliar);
                strcat(mensagem,"   | ");
            }else {
                strcat(mensagem," ");
                strcat(mensagem,auxiliar);
                strcat(mensagem,"  | ");
            }
        }else
            strcat(mensagem,"      | ");

        if(countNew != 0){
            for (int i = 0; i < countNew; i++) {
                bzero(auxiliar,sizeof (int));
                strcat(mensagem,"P");
                snprintf(auxiliar,sizeof (int),"%d",newAux[i]);
                strcat(mensagem,auxiliar);
                strcat(mensagem,"  ");
                aux += 4;
            }
        }
        for(int i = aux; i < 9 ; i++){
            strcat(mensagem," ");
            if(i+1 == 9)
                strcat(mensagem,"|");
        }

        aux = 0;

        if(countExit != 0){
            for (int i = 0; i < countExit; i++) {
                bzero(auxiliar,sizeof (int));
                strcat(mensagem,"P");
                snprintf(auxiliar,sizeof (int),"%d",exitAux[i]);
                strcat(mensagem,auxiliar);
                strcat(mensagem,"  ");
                aux += 4;
            }
        }
        for(int i = aux; i < 10 ; i++){
            strcat(mensagem," ");
            if(i+1 == 10)
                strcat(mensagem,"|");
        }

        aux = 0;

        if(countReady != 0){
            for(int i = 0;i < countReady;i++){
                bzero(auxiliar,sizeof (int));
                strcat(mensagem,"P");
                snprintf(auxiliar,sizeof (int),"%d",readyAux[i]);
                strcat(mensagem,auxiliar);
                strcat(mensagem,"  ");
                aux += 4;
            }
        }

        for(int i = aux; i < 41 ; i++){
            strcat(mensagem," ");
        }

        if(countRun != 0) {
            bzero(auxiliar,sizeof (int));
            snprintf(auxiliar,sizeof (int),"%d",runAux[0]);
            strcat(mensagem,"| P");
            strcat(mensagem,auxiliar);
            strcat(mensagem,"   | ");
        }else{
            strcat(mensagem,"|      | ");
        }

        for(int i = 0;i < countBlocked;i++){
            bzero(auxiliar,sizeof (int));
            snprintf(auxiliar,sizeof (int),"%d",blockedAux[i]);
            strcat(mensagem,"P");
            strcat(mensagem,auxiliar);
            strcat(mensagem,"  ");
        }
    }
    puts(mensagem);
}

bool verificaColuna(int max,int programa[][max],int coluna,int numeroProcessos){

    int contador = 0;

    for(int i = 0;i<numeroProcessos;i++){

        if(programa[i][coluna] == 0){

            contador++;

        }

    }

    if(contador == numeroProcessos) return true;

    return false;

}

bool terminouProcesso(int max , int programas [][max], int coluna,int linha){

    if( coluna + 1 < max && programas[linha][coluna+1] == 0 || coluna + 1 == max){

        return true;

    }

    return false;

}

//retorna true caso y esteja contido em algum dos elementos de posiçoes
bool auxilio (int y , int posicoes[100]){
    for(int i = 0; i < 100 ; i+=4){

        if((y >= posicoes[i] && y <=posicoes[i+1]) || (y >= posicoes[i+2] && y <= posicoes[i+3])){
            return true;
        }
    }
    return false;
}


//função que retorna a posição em que deve alocar os dados e as isntruções em memória tendo em conta o algoritmo bestFit
int bestFit(int posicoes[], int espacoAlocar){
    int array[100];
    int auxArray = 0;

    for(int i = 0; i < 200; i++) {
        if(!auxilio(i,posicoes)){
            array[auxArray] = i;
            auxArray++;
            for(int j = i; j < 200 ; j++){
                if(auxilio(j,posicoes)){
                    array[auxArray] = j - 1;
                    auxArray++;
                    i = j;
                    break;
                }

                if(j + 1 == 200) {
                    array[auxArray] = j;
                    auxArray++;
                    i = j;
                }
            }
        }
    }

    int menor = 200;
    int posicao = 0;
    for(int i = 0; i < auxArray ; i+=2){
        if((array[i+1] - array[i]) + 1 < menor && (array[i+1] - array[i]) + 1 >= espacoAlocar){
            menor = array[i+1] - array[i];
            posicao = array[i];
        }
    }

    if(menor == 200){
        printf("-> impossível criar processo: espaço em memória insuficiente\n");
        return -5;
    }

    return posicao;
}

bool auxTerminar(int max , int programas[][max],int linha,int instantes_de_tempo[]){
    if(instantes_de_tempo[linha] == 0){
        return true;
    }
    return false;
}

int frk(int max1 , int programas[][max1],int processo,int posicoes[],int mem[],struct Queue* ready,int instantes_de_tempo[],int auxposicoes[],int numeroProcessos){
    int newProcess;
    int max = posicoes[4 * processo + 1] - posicoes[4 * processo];
    bool x = false;

    for(int i = 0;i < numeroProcessos;i++){
        if(auxTerminar(max,programas,i,instantes_de_tempo)){
            newProcess = i;
            x = true;
            break;
        }
    }

    if(!x)
        newProcess = numeroProcessos;

    int h = bestFit(posicoes,max + 1);
    if( h == -5){
        return -5;
    }else{
        posicoes[4 * newProcess] = h;

        for (int i = 0; i <= max; i++) {
            mem[h] = -1;
            h++;
        }

        posicoes[4 * newProcess + 1] = h-1;

        posicoes[4 * newProcess + 2] = posicoes[4 * processo + 2];

        posicoes[4 * newProcess + 3] = posicoes[4 * processo + 3];

        enqueue(ready,newProcess + 1);

        instantes_de_tempo[newProcess] = instantes_de_tempo[processo];

        auxposicoes[newProcess] = auxposicoes[processo];

    }

    return newProcess + 1;
    
}

int main()
{

    //ler do ficheiro
    FILE* file = fopen("input.txt","r");

    if(file == NULL){
        perror("Erro ao abrir o ficheiro ");
    }

    int numeroProcessos = 0;

    char codigo[5],valor[5];


    while(fscanf(file,"%s",codigo) != EOF){
        if(strcmp(codigo,"INI") == 0){
            numeroProcessos++;
        }
    }
    fclose(file);

    int instanteDeCadaProcesso[numeroProcessos] ,numInstantes = 0, count = -1;

    bzero(codigo,5);

    file = fopen("input.txt","r");

    for (int i = 0; i < ((sizeof instanteDeCadaProcesso) / (sizeof (int))); ++i) {
        instanteDeCadaProcesso[i] = 0;
    }
    while(fscanf(file,"%s",codigo) != EOF){
        if(strcmp(codigo,"INI") == 0){
            instanteDeCadaProcesso[count]--;
            count++;
        }else{
            instanteDeCadaProcesso[count]++;
        }
    }
    fclose(file);
    instanteDeCadaProcesso[count]--;

    int max = 0;
    for(int i = 0; i < numeroProcessos;i++){
        if(instanteDeCadaProcesso[i] + 2 > max)
            max = instanteDeCadaProcesso[i] + 2;
    }

    file = fopen("input.txt","r");
    bzero(codigo,5);

    int programas[numeroProcessos][max];
    for(int i = 0;i < numeroProcessos;i++){
        for(int j = 0;j < max;j++){
            if(j == 1){
                programas[i][j] = instanteDeCadaProcesso[i] / 2;
            }else {
                if(j > instanteDeCadaProcesso[i] + 1){
                    programas[i][j] = 0;
                }else {
                    fscanf(file, "%s", codigo);
                    if (strcmp(codigo, "INI") == 0) {
                        fscanf(file, "%s", codigo);
                    }
                    if (strcmp(codigo, "ZER") == 0)
                        programas[i][j] = 0;
                    else if (strcmp(codigo, "CPY") == 0)
                        programas[i][j] = 1;
                    else if (strcmp(codigo, "DEC") == 0)
                        programas[i][j] = 2;
                    else if (strcmp(codigo, "FRK") == 0)
                        programas[i][j] = 3;
                    else if (strcmp(codigo, "JFW") == 0)
                        programas[i][j] = 4;
                    else if (strcmp(codigo, "JBK") == 0)
                        programas[i][j] = 5;
                    else if (strcmp(codigo, "DSK") == 0)
                        programas[i][j] = 6;
                    else if (strcmp(codigo, "JIZ") == 0)
                        programas[i][j] = 7;
                    else if (strcmp(codigo, "PRT") == 0)
                        programas[i][j] = 8;
                    else if (strcmp(codigo, "HLT") == 0)
                        programas[i][j] = 9;
                    else
                        programas[i][j] = (int) strtol(codigo, NULL, 10);
                }
            }
        }
    }

    int mem[200];

    int posicoes[100];//4 posições para cada processo ,ou seja, o processo 3 as posições será 4 * (3 - 1)

    for (int i = 0 ; i < 100 ; i++){
        posicoes[i] = -5;
    }

    int instantes_de_tempo[20];
    for(int i = 0;i < numeroProcessos ; i++){
        instantes_de_tempo[i] = programas[i][1];
    }

    int auxPosicoes[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //cada elemento corresponde em que instrução de running vai , por exemplo , a posição zero corresponde ao primeiro processo

    struct Queue* ready = createQueue(50);

    struct Queue* blocked = createQueue(50);

    struct Queue* running = createQueue(50);

    struct Queue* new = createQueue(50);

    struct Queue* exit = createQueue(50);

    int linha = 0;

    int coluna = 0;

    int instantes = 0;

    int auxquantum = 0;

    int contadorBlocked = 0;

    bool run = false , dontRun = false , dontBlock = false , dontRunNew = false , auxBlock = false , aux5 = false , lastInExit = false;

    bool terminarPrograma = false;

    bool auxterminar = false;

    int errorSegmentacao = -1;

    int auxMem = 0 , auxiliar = 0, st = -1;

    int readyAux[50],blockedAux[50],runAux[50],newAux[50],exitAux[50],countNew = 0,countReady = ready->size,countBlocked = blocked->size,countRun = running->size,countExit = exit->size;


    Output(newAux,exitAux,readyAux,runAux,blockedAux,instantes,st,countReady,countRun,countBlocked,countNew,countExit);

    while(linha<numeroProcessos){
        if(!terminouProcesso(max,programas,coluna,linha)) {
            if (programas[linha][coluna] == 0) {
                if (isEmpty(running)){
                    newAux[countNew] = linha + 1;
                    countNew++;
                    enqueue(running, linha + 1);
                } else {
                    newAux[countNew] = linha + 1;
                    countNew++;
                    enqueue(ready, linha + 1);
                }

                int max1 = 0;
                int x = 2;
                //calculo para var_x máximo
                for(int i = 0; i < instantes_de_tempo[linha] && instantes_de_tempo[linha] < 201; i++){
                    if (programas[linha][x] == 1 || programas[linha][x] == 2 || programas[linha][x] == 3){
                        if (programas[linha][x + 1] > max1)
                            max1 = programas[linha][x + 1];
                    }
                    x+=2;
                }

                if(200 - (auxMem + max1 + instantes_de_tempo[linha]) < 0){
                    if(findInt(linha,ready,numeroProcessos)){
                        dequeue(ready);
                    }else
                        dequeue(running);
                    auxiliar = 1;
                }else{

                    posicoes[4 * (linha)] = auxMem;

                    //alocar dados em memória
                    for (int i = 0; i <= max1; i++) {
                        mem[auxMem] = -1;
                        auxMem++;
                    }


                    posicoes[4 * (linha) + 1] = auxMem - 1;

                    ////////////////////////////////////////////

                    posicoes[4 * (linha) + 2] = auxMem;

                    x = 2;
                    //alocar instruçoes em memoria
                    for (int i = 0; i < instantes_de_tempo[linha] * 2; i++) {
                        mem[auxMem] = programas[linha][x];
                        x++;
                        auxMem++;
                    }

                    posicoes[4 * (linha) + 3] = auxMem - 1;
                }

            }else {
                programas[linha][0] --;
                enqueue(new, linha + 1);
            }
        }
            linha++;
    }

    instantes++;

    Output(newAux,exitAux,readyAux,runAux,blockedAux,instantes,st,countReady,countRun,countBlocked,countNew,countExit);
    bzero(newAux,50);
    countNew = 0;

    if (auxiliar == 1)
        printf("-> impossível criar processo: espaço em memória insuficiente\n");

    for(coluna = 0;coluna<=max && !auxterminar;coluna++){

        instantes++;

        if(!auxterminar){
            bzero(newAux,50);
            bzero(exitAux,50);
            bzero(readyAux,50);
            bzero(blockedAux,50);
            bzero(runAux,50);
            countReady = ready->size;countBlocked = blocked->size;countRun = running->size,countNew = 0,countExit = exit->size;
            for(int i=0; i < ready->size;i++){
                readyAux[i] = ready->array[ready->front+i];
            }

            for(int i=0; i < blocked->size;i++){
                blockedAux[i] = blocked->array[blocked->front + i];
            }

            for(int i=0; i < running->size;i++){
                runAux[i] = running->array[running->front + i];
            }

            for(int i = 0;i < new->size;i++){
                int j = new->array[new->front + i];
                if(programas[j-1][0] == 0) {
                    newAux[countNew] = j;
                    countNew++;
                }
            }

            for(int i=0; i < exit->size;i++){
                exitAux[i] = exit->array[exit->front + i];
            }

        }

        if(st != -1){
            st = -1;
        }

        if(instantes == 100){
            break;
        }

        for (linha = 0; linha < numeroProcessos; linha++){

            if(!isEmpty(running) && front(running) == linha + 1 && !run){
                int y = coluna;
                auxquantum++;

                int codigo1 = 0;
                int var = 0;

                instantes_de_tempo[linha]--;

                    codigo1 = mem[posicoes[4 * (linha) + 2] + auxPosicoes[linha]];
                    auxPosicoes[linha]++;
                    var = mem[posicoes[4 * (linha) + 2] + auxPosicoes[linha]];
                    auxPosicoes[linha]++;

                    int k;
                    switch (codigo1) {
                        case 0:
                            mem[posicoes[4 * (linha)]] = var;
                            break;

                        case 1:
                            mem[posicoes[4 * (linha)] + var] = mem[posicoes[4 * (linha)]];
                            break;

                        case 2:
                            mem[posicoes[4 * (linha)] + var]--;
                            break;

                        case 3:
                             k = frk(max,programas,linha,posicoes,mem,ready,instantes_de_tempo,auxPosicoes,numeroProcessos);

                            if( k == -5)
                                printf("-> fork sem sucesso\n");
                            else{
                                if(k >= numeroProcessos + 1){
                                    numeroProcessos++;
                                }
                                mem[posicoes[4 * linha] + var] = k; //var_x = PID do processo criado
                                mem[posicoes[4 * (k - 1)] + var] = 0; //var_x = 0 , pois é o filho
                            }
                            break;

                        case 4:
                            auxPosicoes[linha] += (var * 2 - 2);
                            if(auxPosicoes[linha] + 1 > (programas[linha][1] * 2)){
                                errorSegmentacao = linha + 1;
                                if(isEmpty(new) && isEmpty(ready) && isEmpty(blocked) && isEmpty(exit)) {
                                    auxterminar = true;
                                    break;
                                }
                                enqueue(exit, dequeue(running));
                                aux5 = true;
                                instantes_de_tempo[linha] = 0;
                            }
                            break;

                        case 5:
                            auxPosicoes[linha] -= (var * 2 + 2);
                            instantes_de_tempo[linha]+=var;
                            if(auxPosicoes[linha] + 1 < 0){
                                errorSegmentacao = linha + 1;
                                if(isEmpty(new) && isEmpty(ready) && isEmpty(blocked) && isEmpty(exit)) {
                                    auxterminar = true;
                                    break;
                                }
                                enqueue(exit, dequeue(running));
                                aux5 = true;
                                instantes_de_tempo[linha] = 0;
                            }
                            break;

                        case 6:
                            enqueue(blocked, dequeue(running));
                            if (!isEmpty(ready))
                                enqueue(running, dequeue(ready));
                            auxquantum = 0;
                            auxBlock = true;
                            run = true;
                            break;

                        case 7:
                            if (var == 0) {
                                auxPosicoes[linha] += 1;
                            }
                            break;

                        case 8:
                            st = mem[posicoes[4 * (linha)] + var];
                            break;

                        default:
                            enqueue(exit, dequeue(running));
                            auxquantum = 0;
                            aux5 = true;
                            instantes_de_tempo[linha] = 0;
                            break;
                    }

                if(!auxBlock) {

                    int h = coluna;

                    if (auxquantum == QUANTUM){
                        //temos que ver se existe algum dos processos seguintes vai de block para ready
                        for (int x = linha + 1; x < numeroProcessos; x++) {
                            coluna = y;
                            if (front(blocked) == x + 1) {
                                while (programas[x][coluna] == 0) {
                                    coluna++;
                                }

                                if (contadorBlocked + 1 == 5 && !terminouProcesso(max,programas, coluna, x)) {
                                    enqueue(ready, x + 1);
                                    dontRun = true;
                                    break;
                                }
                            }
                        }

                        if(!aux5) {
                            if (!dontRunNew)
                                enqueue(ready, dequeue(running));
                            else
                                dequeue(running);
                        }
                        if (!isEmpty(ready)) {
                            run = true;
                            enqueue(running, dequeue(ready));
                        }
                        auxquantum = 0;
                    }
                    coluna = h;

                    if (instantes_de_tempo[linha] == 0){
                        if(!aux5) {
                            if (instantes_de_tempo[linha] > 0) {
                                enqueue(blocked, dequeue(running));
                                auxquantum = 0;
                            } else {
                                auxquantum = 0;
                                enqueue(exit, dequeue(running));
                            }
                        }
                        if (!isEmpty(ready)) {
                            run = true;
                            enqueue(running, dequeue(ready));
                        }
                    }
                }

                coluna = y;

            }
            else if (!isEmpty(new) && findInt(linha,new,numeroProcessos) && programas[linha][0] == 0){
                int y = coluna;
                programas[linha][coluna] = 0;

                if (programas[linha][coluna] == 0) {
                    //temos que ver se algum dos processos seguintes vai passar de blocked ou running para ready
                    for (int x = linha + 1; x < numeroProcessos; x++) {
                        coluna = y;
                        if (front(blocked) == x + 1) {
                            while (programas[x][coluna] == 0) {
                                coluna++;
                            }

                            if (contadorBlocked + 1 == 5 && !terminouProcesso(max,programas, coluna, x)) {
                                enqueue(ready, x + 1);
                                dontRun = true;
                                break;
                            }

                        }
                    }

                    for (int x = linha + 1; x < numeroProcessos; x++) {
                        coluna = y;
                        if (front(running) == x + 1) {
                            while (programas[x][coluna] == 0) {
                                coluna++;
                            }

                            if (auxquantum + 1 == QUANTUM && programas[x][coluna] != 0) {
                                enqueue(ready, x + 1);
                                dontRunNew = true;
                                break;
                            }
                        }
                    }


                    //ALOCAÇÃO
                    int max1 = 0;
                    int x = 2;
                    //calculo para var_x máximo
                    for (int i = 0; i < instantes_de_tempo[linha]; i++) {
                        if (programas[linha][x] == 1 || programas[linha][x] == 2 || programas[linha][x] == 3){
                            if (programas[linha][x + 1] > max1)
                                max1 = programas[linha][x + 1];
                        }
                        x += 2;
                    }

                    int h = bestFit(posicoes, (max1 + (instantes_de_tempo[linha] * 2)) + 1);

                    if (h != -5) {

                        posicoes[4 * ((linha + 1) - 1)] = h;

                        //alocar em memória
                        for (int i = 0; i <= max1; i++) {
                            mem[h] = -1;
                            h++;
                        }


                        posicoes[4 * ((linha + 1) - 1) + 1] = h - 1;

                        ///////////////////////////////////////

                        posicoes[4 * ((linha + 1) - 1) + 2] = h;

                        x = 2;
                        //alocar instruçoes em memoria
                        for (int i = 0; i < instantes_de_tempo[linha] * 2; i++) {
                            mem[h] = programas[linha][x];
                            x++;
                            h++;
                        }

                        posicoes[4 * ((linha + 1) - 1) + 3] = h - 1;

                        if (isEmpty(running)) {
                            enqueue(running, linha + 1);
                            retira(linha,new);
                        }else {
                            enqueue(ready, linha + 1);
                            retira(linha,new);
                        }
                    }else
                        retira(linha,new);
                }

                coluna = y;

            }
            else if(!isEmpty(blocked) && front(blocked) == linha + 1 && !dontBlock){
                contadorBlocked++;
                if(contadorBlocked == 5){
                        if(!isEmpty(running)){
                            if(!dontRun){
                                enqueue(ready, dequeue(blocked));
                            }else{
                                dequeue(blocked);
                            }
                        }else {
                            enqueue(running, dequeue(blocked));
                        }
                        dontBlock = true;
                    contadorBlocked = 0;
                }

            }
            else if(!isEmpty(exit) && findInt(linha,exit,numeroProcessos)){
                //fazer a gestão de memória ou seja libertar a memória alocada do processo
                dequeue(exit);
                lastInExit = true;
                for (int i = 0; i < 4; ++i) {
                    posicoes[4 * (linha) + i] = -5;
                }

            }else{
                if (findInt(linha,new,numeroProcessos)){

                    programas[linha][0]--;

                }

                if(isEmpty(exit) && isEmpty(new) && isEmpty(ready) && isEmpty(running) && isEmpty(blocked)){
                    auxterminar = true;
                }

            }

        }

        run = false,dontRun = false,dontBlock = false,dontRunNew = false , auxBlock = false , aux5 = false;

        if(!verificaColuna(max,programas,coluna,numeroProcessos) && !auxterminar){

            coluna--;

        }else if(coluna + 1 == max && !terminarPrograma && !auxterminar) {

            coluna--;

            terminarPrograma = true;

        }


        if(!auxterminar || lastInExit){
            Output(newAux,exitAux,readyAux,runAux,blockedAux,instantes,st,countReady,countRun,countBlocked,countNew,countExit);
            bzero(newAux,50);
            countNew = 0;
        }

        if(errorSegmentacao != -1){
            printf("-> erro de segmentação do processo %d\n",errorSegmentacao);
            errorSegmentacao = -1;
        }

        lastInExit = false;
    }

    return 0;

}
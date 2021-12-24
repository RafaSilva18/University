#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>

void print_ttt(char ttt[]) // prints the board
{
    int i,
            l = 0;

    for (i = 0; i < 9; i++) {
        if (ttt[i] == 2) printf(" %d ", i+1);
        else if (ttt[i] == 0) printf (" X ");
        else if (ttt[i] == 1) printf (" O ");

        if (i == 2 || i == 5 || i == 8) printf("\n");
        if (i == 2 || i == 5) printf("---+---+---\n");
        if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7) printf("|");
    }
    printf("\n");
}

int try_play(char ttt[], int spot, char mark) // tries to make a play
{
    if (ttt[spot] == 2) { // blank spot, can play
        ttt[spot] = mark;
        return 1;
    }
    else {
        return 0;
    }
}

int check_win(char ttt[]) // checks if someone won
{
    int who = -1;

    if (
        //lines
            ((who = ttt[0]) == ttt[1] && ttt[1] == ttt[2] && who != 2) ||
            ((who = ttt[3]) == ttt[4] && ttt[4] == ttt[5] && who != 2) ||
            ((who = ttt[6]) == ttt[7] && ttt[7] == ttt[8] && who != 2) ||
            //columns
            ((who = ttt[0]) == ttt[3] && ttt[3] == ttt[6] && who != 2) ||
            ((who = ttt[1]) == ttt[4] && ttt[4] == ttt[7] && who != 2) ||
            ((who = ttt[2]) == ttt[5] && ttt[5] == ttt[8] && who != 2) ||
            //diagonals
            ((who = ttt[0]) == ttt[4] && ttt[4] == ttt[8] && who != 2) ||
            ((who = ttt[2]) == ttt[4] && ttt[4] == ttt[6] && who != 2)
            )
    {
        return who;
    }
    else return -1;
}

char get_move(char ttt[], int aux)
{
    char move = 0;
    char buf[10];

    while (move < '1' || move > '9') {
        if(aux<1){
            fgets(buf, 5, stdin);
            bzero(buf, 10);
        }
        fgets(buf, 5, stdin);
        move = buf[0];


        if (!try_play(ttt, move - '1', 1)) {
            printf("Spot taken, choose another!\n");
            move = 0;


        }
    }

    return move;
}

bool checkFile(char nome[],char pass[],FILE *file){
    char getWord[30];

    while(fscanf(file,"%s",getWord) != EOF){
        if(strcmp(getWord,nome) == 0){
            bzero(getWord,30);
            fscanf(file,"%s",getWord);
            if(strcmp(getWord,pass) == 0){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

bool verificaSeUtilizadorConectado(char nome[],FILE *file){
    char getWord[30];

    while(fscanf(file,"%s",getWord) != EOF){
        if(strcmp(getWord,nome) == 0){
            return true;
        }
    }
    return false;
}


int main(int argc, char *argv[]) {
    FILE *file;
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    portno = 1300;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }else{
        printf("Socket Created\n");
    }

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(1);
    }else{
        printf("Server connected\n");
    }

    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(2);
    }else{
        printf("Client connected to server\n");
    }

    FILE *file1 = fopen("autenticatedFile","a");


    fd_set read_fd;
    fd_set write;
    fd_set exception;
    int fiscal = 0;

    int m=0;

    char response[50],nome[50],pass[50];
    do {
        printf("Já possui autenticação?(sim/nao) ");
        scanf("%s", response);
    }while(strcmp(response,"sim") != 0 && strcmp(response,"nao") != 0);

    bool x = false;
    //caso utilizador já estiver autenticado coloca nome e pass envia-os ao servidor e este verifica se existe ou nao
    while(strcmp(response,"sim") == 0 && !x){
        printf("Insira Username: ");
        scanf("%s",nome);
        printf("Insira Password: ");
        scanf("%s",pass);
        file = fopen("aut","r");
        if(file == NULL){
            printf("Erro a ler ficheiro\n");
            exit(1);
        }
        x = checkFile(nome,pass,file);
        fclose(file);
        if(!x){
            printf("Username ou password errada\n");
        }
    }

    if(strcmp(response,"nao") == 0){
        printf("Insira Username: ");
        scanf("%s",nome);
        printf("Insira Password(menor que 30 caracteres): ");
        scanf("%s",pass);
        file = fopen("aut","a");
        if(file == NULL){
            printf("Erro a ler ficheiro");
            exit(1);
        }
        fprintf(file," %s %s",nome,pass);
        fclose(file);
    }



    send(sockfd,"aut_time",sizeof "aut_time",0);
    fprintf(file1," %s",nome);
    fclose(file1);

    char mensagem1[256];
    recv(sockfd,mensagem1,sizeof mensagem1,0);

    if(strcmp(mensagem1,"not this client") != 0){
        printf("Mensagens recebidas enquanto esteve offline : %s\n",mensagem1);
    }else{
        printf("Não recebeu nenhuma mensagem enquanto esteve offline\n");
    }


    int resposta;
    bool k = true;
    while(k){
        do {
            printf("O que deseja fazer (1 -> 1-1 em tempo real , 2 -> 1-todos em tempo real , 3 -> 1-1 em diferido, 4 -> jogo do galo) : \n");
            scanf("%d", &resposta);
        } while (resposta < 1 || resposta > 4);



        char utilizadorParaConversa[20];
        while (resposta == 1){
            printf("Insira o Username de quem deseja falar: \n");
            scanf("%s", utilizadorParaConversa);
            file1 = fopen("autenticatedFile", "r");
            if (verificaSeUtilizadorConectado(utilizadorParaConversa, file1)) {
                printf("O Username que inseriu encontra-se Online\n");
                printf("Se desejar sair do programa insira SAIR , caso deseje voltar ao menu insira VOLTAR ATRAS\n");
                break;
            } else
                printf("O Username que inseriu não se encontra disponível\n");
            fclose(file1);
        }

        if (resposta == 2) {
            printf("Entrou no modo 1-todos em tempo real\n");
        }else if(resposta == 3){
            printf("Insira o username : \n");
            scanf("%s",utilizadorParaConversa);
        }else if(resposta == 4){
            printf("Insira o Username de quem deseja jogar: \n");
            scanf("%s", utilizadorParaConversa);
            file1 = fopen("autenticatedFile", "r");
            if (verificaSeUtilizadorConectado(utilizadorParaConversa, file1)) {
                printf("O Username que inseriu encontra-se Online\n");
                printf("Se desejar sair do programa insira SAIR , caso deseje voltar ao menu insira VOLTAR ATRAS\n");
            } else
                printf("O Username que inseriu não se encontra disponível\n");
            fclose(file1);
        }





        char mensagem[256];
        char umUm[20] = "1-1 em tempo real";
        char diferido[20] = "1-1 em diferido";
        char todos[20] = "1-todos";
        char aux[20];
        int count = 0;
        char msg[256];
        char o[256];
        long send_count;
        char aux1[20];


        if(resposta==4){

            bzero(buffer, 256);
            char tictactoe[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
            print_ttt(tictactoe);
            printf("\nSeja o primeiro a jogar ao escolher uma posicao.\n");
            printf("\nOu espere pela jogada do oponente.\n");
            int counter, cont=0;

            while (m >= 0) {
                FD_ZERO(&read_fd);
                FD_SET(STDIN_FILENO, &read_fd);
                FD_SET(sockfd, &read_fd);

                FD_ZERO(&write);

                FD_SET(sockfd, &write);


                FD_ZERO(&exception);
                FD_SET(STDIN_FILENO, &exception);
                FD_SET(sockfd, &exception);
                count = 0;
                select(sockfd + 1,&read_fd,NULL,NULL,NULL);

                if(FD_ISSET(sockfd,&read_fd)){

                    if (fiscal >= 0){

                        fiscal=0;

                        recv(sockfd,buffer,255,0);
                        int check = try_play(tictactoe, atoi(buffer)-1, 0);

                        if (buffer[0] == 'w'){

                            bzero(buffer, 256);
                            print_ttt(tictactoe);
                            printf("\n You win, congrats!\n");
                            close(sockfd);
                            m = -1;
                            break;
                        }


                        int win = check_win(tictactoe);
                        if (win == 0) {
                            print_ttt(tictactoe);
                            printf("Opponent win!! Better luck next time.\n");
                            bzero(buffer, 256);
                            buffer [0]= 'w';    //nao deve de estar a enviar
                            send(sockfd, buffer, strlen(buffer), 0 );
                            m =-1;
                            break;
                        }
                        counter = 0;
                        for (int i = 0; i < 9; i++) {
                            if (tictactoe[i] != 2) {
                                counter++;
                            }
                        }
                        // ve se houve empate
                        if (counter==9){
                            print_ttt(tictactoe);
                            printf("\nYou and the opponent! tied Restart the game if you want to play again.\n");
                            bzero(buffer, 256);
                            m =-1;
                            break;
                        }


                        printf("\n|||| TABULEIRO ATUALIZADO E JOGADA RECEBIDA ||||\n");
                        print_ttt(tictactoe);
                        size_t len = strlen(buffer);
                        if(len > 0 && buffer[len - 1] == '\n')
                            buffer[len - 1] = '\0';
                        bzero(buffer,256);
                        printf("\nNova jogada ou espere pela jogada do oponente:\n");


                    }

                } else if(FD_ISSET(sockfd,&write)){

                    if(fiscal<1){
                        fiscal += 1;
                        buffer [0]= get_move(tictactoe, cont);
                        cont++;   // para nao dar erro, é o aux da funçao get move
                        send_count = send(sockfd,buffer, strlen(buffer),0);
                        if(send_count < 0){
                            printf("Error send");
                            break;
                        }

                        int win = check_win(tictactoe);
                        if (win == 1) {
                            print_ttt(tictactoe);
                            printf("You win!!Congrats!!\n");
                            bzero(buffer, 256);
                            buffer [0]= 'w';    //nao deve de estar a enviar
                            send(sockfd, buffer, strlen(buffer), 0 );
                            m =-1;
                            break;
                        }

                        counter = 0;
                        for (int i = 0; i < 9; i++) {
                            if (tictactoe[i] != 2) {
                                counter++;
                            }
                        }
                        // ve se houve empate
                        if (counter==9){
                            printf("\nYou and the opponent tied. Restart the game if you want to play again.\n");
                            bzero(buffer, 256);
                            m =-1;
                            break;
                        }
                        printf("\n|||| TABULEIRO ATUALIZADO ||||\n");
                        print_ttt(tictactoe);
                        printf("\nNova jogada ou espere pela jogada do oponente:\n");


                    }else{
                        printf("Não pode jogar outra vez, espere pelo a jogada do oponente.\n");
                        char A[2];//para correçao de erros
                        gets(A);
                    }
                }
            }

        }
        if(resposta != 4)
            for (;;) {

                FD_ZERO(&read_fd);
                FD_SET(STDIN_FILENO, &read_fd);
                FD_SET(sockfd, &read_fd);

                FD_ZERO(&write);

                FD_SET(sockfd, &write);

                memset(mensagem, 0, 256);

                memset(aux, 0, 20);

                memset(msg, 0, 256);

                memset(o, 0, 256);

                memset(aux1, 0, 20);

                select(sockfd + 1, &read_fd, NULL, NULL, NULL);

                if (FD_ISSET(sockfd, &read_fd)) {

                    read(sockfd, mensagem, 256);
                    if (resposta == 1) {
                        printf("Mensagem recebida : %s", mensagem);
                    } else if (resposta == 2)
                        printf("%s", mensagem);

                    size_t len = strlen(mensagem);
                    if (len > 0 && mensagem[len - 1] == '\n')
                        mensagem[len - 1] = '\0';


                } else if (FD_ISSET(sockfd, &write)) {
                    if (resposta == 1) {
                        send_count = send(sockfd, umUm, sizeof umUm, 0);
                        if (send_count < 0) {
                            printf("Error send");
                            break;
                        }

                        recv(sockfd, aux, sizeof aux, 0);

                        if (strcmp(aux, "Username?") == 0) {
                            send(sockfd, utilizadorParaConversa, sizeof utilizadorParaConversa, 0);
                        }


                        recv(sockfd, aux1, sizeof aux1, 0);

                        if (strcmp(aux1, "all ok") == 0) {
                            if (count < 1) {
                                fgets(o, 256, stdin);
                                count++;
                            }
                            fgets(msg, 256, stdin);

                            if(strcmp(msg,"VOLTAR ATRAS\n") == 0)
                                break;
                            else if(strcmp(msg,"SAIR\n") == 0) {
                                k = false;
                                break;

                            }

                            send_count = send(sockfd, msg, strlen(msg), 0);
                            if (send_count < 0) {
                                printf("Error send");
                                break;
                            }

                        }
                    } else if (resposta == 2) {
                        send_count = send(sockfd, todos, sizeof todos, 0);
                        recv(sockfd, aux, sizeof aux, 0);
                        if (count < 1) {
                            fgets(o, 256, stdin);
                            count++;
                        }
                        fgets(msg, 256, stdin);
                        if(strcmp(msg,"VOLTAR ATRAS\n") == 0)
                            break;
                        else if(strcmp(msg,"SAIR\n") == 0)
                            return 0;

                        send_count = send(sockfd, msg, strlen(msg), 0);
                        if (send_count < 0) {
                            printf("Error send");
                            break;
                        }
                    }else if(resposta == 3){
                        send(sockfd,diferido,sizeof diferido,0);

                        recv(sockfd,aux,sizeof aux,0);

                        send(sockfd,utilizadorParaConversa,sizeof utilizadorParaConversa,0);

                        recv(sockfd,aux1,sizeof aux1,0);

                        if (count < 1) {
                            fgets(o, 256, stdin);
                            count++;
                        }

                        fgets(msg,256,stdin);

                        if(strcmp(msg,"VOLTAR ATRAS\n") == 0)
                            break;
                        else if(strcmp(msg,"SAIR\n") == 0)
                            return 0;

                        send_count = send(sockfd,msg,sizeof msg,0);
                        if (send_count < 0) {
                            printf("Error send");
                            break;
                        }
                    }
                }
            }
    }
    return 0;
}
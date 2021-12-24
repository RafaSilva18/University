#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#define PORT "1300"   // port we're listening on

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

typedef struct{
    char nome[20];
    char mensagem[256];
}mensagemDiferido;

int main(void)
{
    FILE *file = fopen("autenticatedFile","w");
    if(file == NULL){
        printf("ERRO A ABRIR FICHEIRO");
    }
    fclose(file);
    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number

    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;

    struct addrinfo hints, *ai, *p;

    mensagemDiferido diferido[100];
    int countDiferido = 0;

    char nomes[10][10];
    int auxString = 0;
    char name[20];
    char pass[20];

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

    // get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL) {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }

    freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    char message[256];
    char username[256];
    char messageToAll[256];
    char getWord[20];
    char numSocket[20];
    char nome[20];
    char usernameDeferido[20];
    char messageDeferido[256];
    char auxMensagemDeferido[500];
    char numSocketDiferido[10];
    // main loop
    for(;;){
        read_fds = master; // copy it
        memset(messageToAll,0,256);
        memset(getWord,0,20);
        memset(numSocket,0,20);
        memset(username,0,256);
        memset(message,0,256);
        memset(buf,0,256);
        memset(nome,0,20);
        memset(usernameDeferido,0,20);
        memset(messageDeferido,0,256);
        memset(auxMensagemDeferido,0,256);
        memset(numSocketDiferido,0,10);
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) {

            if (FD_ISSET(i, &read_fds)) {// we got one!!

                if (i == listener) {

                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                                   (struct sockaddr *)&remoteaddr,
                                   &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {

                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntop(remoteaddr.ss_family,
                                         get_in_addr((struct sockaddr*)&remoteaddr),
                                         remoteIP, INET6_ADDRSTRLEN),
                               newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0){
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                            memset(buf,0,256);
                            char aux[20][40];
                            int auxaux = 0;
                            char word[40];
                            file = fopen("autenticatedFile","r");
                            while(fscanf(file,"%s",word) != EOF){
                                strcpy(aux[auxaux],word);
                                auxaux++;
                            }
                            fclose(file);
                            file = fopen("autenticatedFile","w");
                            for(int k = 0; k < auxaux ; k++){
                                char auxiliar[sizeof (int)];
                                snprintf(auxiliar,sizeof (int), "%d",i);
                                if(strcmp(aux[k],auxiliar) != 0 && strcmp(aux[k+1],auxiliar) != 0){
                                    fprintf(file," %s",aux[k]);
                                }
                            }
                            fclose(file);
                        }else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    }else if(strcmp(buf,"1-1 em tempo real") == 0){
                        send(i,"Username?",sizeof "Username?",0);
                        //Recebe nome de utilizador para enviar as mensagens
                        recv(i, username, sizeof username, 0);

                        file = fopen("autenticatedFile","r");
                        bool x = false;
                        while(fscanf(file,"%s",getWord) != EOF){
                            if(strcmp(getWord,username) == 0){
                                x = true;
                                fscanf(file,"%s",numSocket);
                            }
                        }
                        fclose(file);
                        send(i,"all ok",sizeof "all ok",0);
                        if(x){
                            read(i,message,sizeof message);
                            if(FD_ISSET(strtol(numSocket,NULL,10),&master)){
                                if (strtol(numSocket,NULL,10) != listener && strtol(numSocket,NULL,10) != i) {
                                    if (send((int)strtol(numSocket,NULL,10), message, sizeof message, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }


                    }else if(strcmp(buf,"aut_time") == 0){
                        FILE *file1 = fopen("autenticatedFile","a");
                        char auxiliar[sizeof (int)];
                        snprintf(auxiliar,sizeof (int), "%d",i);
                        fprintf(file1," %s",auxiliar);
                        fclose(file1);
                        bool t = false;
                        int auxQ;
                        file1 = fopen("autenticatedFile","r");
                        char getWord1[20];
                        while(fscanf(file1,"%s",getWord1) != EOF){
                            fscanf(file1,"%s",numSocketDiferido);
                            for(int q = 0; q < countDiferido; q++){
                                if(strcmp(diferido[q].nome,getWord1) == 0 && strtol(numSocketDiferido,NULL,10) == i) {
                                    strcat(auxMensagemDeferido,diferido[q].mensagem);
                                    strcpy(diferido[q].mensagem,"");
                                    t = true;
                                }
                            }
                        }

                        if(!t){
                            send(i,"not this client",sizeof "not this client",0);
                        }else{
                            send(i, auxMensagemDeferido, sizeof auxMensagemDeferido, 0);

                        }
                    }
                    else if(strcmp(buf,"1-1 em diferido") == 0){
                        send(i,"0",sizeof "0",0);

                        recv(i,usernameDeferido,sizeof usernameDeferido,0);

                        strcpy(diferido[countDiferido].nome,usernameDeferido);

                        send(i,"0",sizeof "0",0);

                        recv(i,messageDeferido,sizeof messageDeferido,0);

                        strcpy(diferido[countDiferido].mensagem,messageDeferido);

                        countDiferido++;

                    }
                    else if (strcmp(buf,"1-todos")==0){
                        bzero(buf,256);
                        send(i,"0",sizeof "0",0);
                        file = fopen("autenticatedFile","r");
                        while(fscanf(file,"%s",getWord) != EOF){//retirar o username de quem eniva a mensagem , fica guardado em username
                            fscanf(file,"%s",numSocket);
                            if(strtol(numSocket,NULL,10) == i){
                                strcpy(username,getWord);
                                break;
                            }

                        }
                        fclose(file);
                        strcat(messageToAll,"Mensagem enviada por ");
                        strcat(messageToAll,username);
                        strcat(messageToAll," : ");


                        strcat(messageToAll,buf);


                        // we got some data from a client
                        for(j = 0; j <= fdmax; j++) {
                            // send to everyone!
                            if (FD_ISSET(j, &master)){
                                // except the listener and ourselves
                                if (j != listener && j != i) {
                                    if (send(j, messageToAll, sizeof messageToAll, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }else{

                        for(j = 0; j <= fdmax; j++) {
                            // send to everyone!
                            if (FD_ISSET(j, &master)) {
                                // except the listener and ourselves
                                if (j != listener && j != i) {
                                    if (send(j, buf, nbytes, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!

    return 0;
}
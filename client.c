#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
int main()
{

    pid_t pid;
    int id;
    char msg[255];//variable qui contiendrat les messages

    struct sockaddr_in informations;  //structure donnant les informations sur le serveur

    /*initialisation du protocole, TCP  l'adresse de connection 127.0.0.1 (en local) et du port du serveur (1400)*/
    informations.sin_family = AF_INET;
    informations.sin_port = htons(2500);
    informations.sin_addr.s_addr = inet_addr("127.0.0.1");

    int socketID = socket(AF_INET, SOCK_STREAM, 0); // creation du socket propre au client

    if (socketID == -1)    //test de création du socket
    {
        perror("socket");
        exit (-1);
    }

    if ((connect(socketID, (struct sockaddr *) &informations, sizeof(struct sockaddr_in))) == -1)   //connexion au serveur
    {
        perror("connect");
        exit (-1);
    }

    if (strcmp(msg, "aurevoir") != 0)
    {
        memset(msg, 0, 255);
        recv(socketID, msg, 255, 0);
        printf ("%s\n", msg);
    }

    do
    {
        id+=1;
        printf ("moi : ");
        fgets(msg, 255, stdin);// le client ecrit son message
        msg[strlen(msg) - 1] = '\0';

        if ((send(socketID, msg, strlen(msg), 0)) == -1)
            perror("send");
        recv(socketID, msg, 255, 0);
        printf ("Phrase reçue : %s\n", msg);

    }
    while (strcmp(msg, "aurevoir") != 0);    // tant que le client n'envoie pas "aurevoir" la conversation n'est pas fini

    shutdown(socketID, SHUT_RDWR);// fermeture du socket

    return 0;

}

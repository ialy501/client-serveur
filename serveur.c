#include<signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    //structure donnant les informations sur le serveur et sur le client
    struct sockaddr_in information_server;
    struct sockaddr_in information_client;

    int socketID = socket(AF_INET, SOCK_STREAM, 0);
    int connexion = 0;
    int pid;
    int id;
    char msg[255];
    char buffer[512];

    id=0;
    socklen_t len = sizeof(struct sockaddr_in); //déclaration d' une variable du type socklen_t qui contiendra la taille de la structure

    if (socketID == -1)
    {
        perror("socket");
        exit(-1);
    }

    /*initialisation du protocole, TCP  l'adresse de connection 127.0.0.1 (en local) et du port du serveur (1400)*/
    memset(&information_server, 0, sizeof(struct sockaddr_in));
    information_server.sin_port = htons(2500);
    information_server.sin_family = AF_INET;

    /* création de la connexion*/
    if ((bind(socketID, (struct sockaddr *) &information_server, sizeof(struct sockaddr))) == -1)
    {
        perror("bind");
        exit(-1);
    }

    /* le serveur écoute si un client cherche à se connecter*/
    if ((listen(socketID, 5)) == -1)
    {
        perror("listen");
        exit (-1);
    }
    while (1)
    {

        memset(&information_client, 0, sizeof(struct sockaddr_in));
        connexion = accept(socketID, (struct sockaddr *) &information_client, &len); //le serveur accepte la connexion

        if (connexion == -1)
        {
            perror("accept");
            exit(-1);
        }
        id+=1;
        /* Create child process */
        pid = fork();

        if (pid < 0)
        {
            perror("ERROR on fork");
            exit(1);
        }
        if (pid == 0)
        {
            /* This is the client process */
            close(socketID);
            printf ("Connexion acceptée de : client %i\n",id);
            memset(msg, 0, 255);
            sprintf(msg,"bienvenu! client %i",id);
            send(connexion, msg, strlen(msg), 0);
            FILE *fp;
            int rpt = 0;
            fp = fopen("fichier.txt","a");
            int mot;
            read(connexion, &mot, sizeof(int));
            while(rpt != mot)
            {
                read(connexion , buffer , 512); 
                fprintf(fp , " %s" , buffer);   
                rpt++;
            }
            printf("Le fichier reçu \n");
            printf("Le doc creer\n");
        }
        else
        {
            close(connexion);

        }

    }
    return 0;

}

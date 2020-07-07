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
    char buffer[512];
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


    memset(msg, 0, 255);
    recv(socketID, msg, 255, 0);
    printf ("%s\n", msg);
    FILE *f;    
    int mot = 0;
    char c;
    f=fopen("texte.txt","r");
    while((c=getc(f))!=EOF)         
    {   
        fscanf(f , "%s" , buffer);
        if(isspace(c)||c=='\t')
        mot++;    
    }             
    write(socketID, &mot, sizeof(int));
       rewind(f);
    char ch ;
    while(ch != EOF)
    {
        fscanf(f , "%s" , buffer);
        write(socketID,buffer,512);
        ch = fgetc(f);
    }    
    printf("Le fichier est envoyer avec succès\n");
    

    shutdown(socketID, SHUT_RDWR);// fermeture du socket

    return 0;

}

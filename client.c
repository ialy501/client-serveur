#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>
                
void error(const char *msg)    
                
int main(int argc, char *argv[])
{
    int sockfd, port, n;            
    struct sockaddr_in serv_addr;  
    struct hostent *server;      
    char buffer[512];
    if (argc < 3)                    
    {
       fprintf(stderr,"usage %s nom du port\n", argv[0]);
       exit(0);
    }
    port = atoi(argv[2]);                     
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) 
        error("Erreur d'ouverture de socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Erreurn hote introuvable\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  
    bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);      
    serv_addr.sin_port = htons(port);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERrreur de connection");   
        bzero(buffer,512); 
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
    write(sockfd, &words, sizeof(int));
       rewind(f);
    char ch ;
    while(ch != EOF)
    {
        fscanf(f , "%s" , buffer);
        write(sockfd,buffer,512);
        ch = fgetc(f);
    }    
    printf("Le fichier est envoyer avec succès\n") 
    close(sockfd);
    return 0;       
}

void error(const char *msg)          
{
    perror(msg);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
                

int main(int argc, char * argv[])           
{
    int sockfd, newsockfd, port;            
    socklen_t clilen;
    char buffer[512];
    struct sockaddr_in serv_addr, cli_addr;  
    int n;
    if (argc < 2) 
    {
        fprintf(stderr,"ERREUR!!!\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("erreur");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    port = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;     
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(port); 
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("erreur");
        exit(1);
    }                                
    listen(sockfd,5);  
    clilen = sizeof(cli_addr);  
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
    if (newsockfd < 0){
        perror("erreur");
        exit(1);
    }
    FILE *fp;
    int rpt = 0;
    fp = fopen("fichier.txt","a");
    int mot;
    read(newsockfd, &mot, sizeof(int));
    while(rpt != mot)
    {
        read(newsockfd , buffer , 512); 
        fprintf(fp , " %s" , buffer);   
        rpt++;
    }
    printf("Le fichier reçu \n");
    printf("Le doc creer\n");
    close(newsockfd);
    close(sockfd);
    return 0; 
}


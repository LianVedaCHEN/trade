#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>
#include "proj1.h"

/* TODO: define Server member functions here */
Server::Server(){
    //initialize the server
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5001);
    i=1;
    // below part is to make the variables "price" and "mytime" could be
    // shared among defferent folks in server 
    price=(float*)mmap(NULL,sizeof(float),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    mytime=(time_t*)mmap(NULL,sizeof(time_t),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    attmpNum=(int*)mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
     *attmpNum=0;
};
int Server::sock(){
   //initialize the socket
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        perror("ERROR on binding");return -3;}
    else{
        return sockfd;
    }
   
    
};
void Server::gen_price(int sockfd){
   //declare some variables needed in this function 
    char buf[256] ;
    int n,j;
    //sleep(1);
     *mytime= time(NULL);
   //below part is to generate the price and update it every 10s
    if( *mytime%10==1||*price==0){
    srand(time(NULL));
    *price=(rand()%100)/100.00;
   
    }
   //if(*price==0) return;//to prevent generate $0.00
   sleep(1); 
  //below part is to sent the price generated to the client
   j = sprintf( buf,  "$%.2f %s",*price , ctime(mytime));
   n = write(sockfd,buf,strlen(buf));
   printf("%s",buf);
   fflush(stdout);
   if (n < 0)
        perror("ERROR writing to socket");
    bzero(buf,255);
    
};
void Server::process_buy_request(int sockfd){
    //declare some variables needed in this function
    int n,j;
    char buf2[256];
    char client_price[10];
    char client_buy_time[33];
    char result[11];
    char clientPrice[10];
    //below part is to get the buy request and read the price 
    //and buying time of client 
    bzero(buf2,255);
    n = read(sockfd,buf2,40);
    if (n < 0){
        perror("ERROR reading from socket");
	exit(1);
    }
     if(n>0){
    *attmpNum= *attmpNum+1;
    printf("The number of attempt is %d\n", *attmpNum);
    }
    //below part is to compare the price from the client 
    //and the price of server and then decide
    //and decide the buying is sucessful or failed
    strcpy(client_buy_time,buf2);
    strncpy(client_price,client_buy_time,5);
    sprintf(clientPrice,"%.2f",*price);
    if(atof(client_price)==atof(clientPrice)){
        strcpy(result,"SUCCESSFUL");
    }
    else{
       strcpy(result,"FAILED");
     }
   //send the result made by server to client
    bzero(buf2,255);
   j=sprintf( buf2,"client buy at $%s\r\nserver sell at $%.2f at %.33sall time approx\nbuy %s from server!\n",client_buy_time,*price,ctime(mytime),result);
    n = write(sockfd,buf2,256);
    if (n < 0){
        perror("ERROR writing to socket");
      exit(1);
    }
   
};

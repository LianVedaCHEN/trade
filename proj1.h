#ifndef PROJ1_H 
#define PROJ1_H

/* TODO: Server and Client classes */

#endif
class Server {
    /* TODO */
private:
    struct sockaddr_in serv_addr;    
    int sockfd,i;
    int* attmpNum;
  float* price;
  float temp_price;
   time_t* mytime;
public:
    Server();
    int sock();
    void gen_price(int sockfd);
    void process_buy_request(int sockfd);

};

class Client {
    /* TO DO */
    
private:
    int sockfd,newsockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    int portnoInside;
    float* price;

public:
    Client( char* name,int portno);
    void get_price();
    void gen_buy_request();
    
};


/*
 * the header files i will need to include
 * 
 * Author: Stephen Lamalie
 * Class: COP4635/ project_1
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>


int main(void)
{
    int ls;                            // listen socket descriptor(reference)
    int s;                           // socket descriptor(reference)
    char buffer [256] ={0};               // data buffer
    char* ptr = buffer;              // data buffer
    int len = 0;                     // number of bytes to send or receive
    int maxLen = sizeof(buffer);      // max number of bytes to receive
    int n = 0;                   // number of bytes for each recv call
    int waitSize =16;         // size of waiting clients
    struct sockaddr_in serverAddr; // server address
    struct sockaddr_in clientAddr; // client address
    socklen_t cltAddr = sizeof(serverAddr); // length of client address
    int SERV_PORT = 8080;


    //create local (server) socket address

    memset(&serverAddr,0,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(SERV_PORT);
     
    // create the listen sicket

    if((ls = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("Error: Listen socket failed");
        exit(1);
    }

    // bind listen socket to local socket address

    if(bind(ls,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0)
    {
        perror("Error binding");
        exit(1);
    }

    // listen for connection requests

    if(listen(ls,waitSize)< 0)
    {
        perror("Error listening");
        exit(1);
    }

    // handle the connection
    for (;;)
    {
        printf("got here_1\n");
        
        //accept connection from client
        if((s = accept(ls,(struct sockaddr*)&serverAddr,(socklen_t*) &cltAddr) < 0))
        {
            perror("Error accepting");
            exit(1);
        }

        // data transfer
    printf("got here_2\n");
        
          // problem child
      
        int count = 0;
        n = recv(s, ptr, maxLen,0);
        printf("%d\n", n);/*
        while(n = recv(s, ptr, maxLen,0) != 0)
        {
            printf("%d\n", n);
            count++;

            ptr += n;
            maxLen -= n;
            len += n;
            
        }*/
        
        //send back all bytes received
        send(s, buffer, len,0);
        //close socket
        close(s);
    }

}

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

int main(int argc, char* argv[])
{

    int s;
    int n;
    char* serverName;
    int serverPort;
    char* myString;
    //char* line = ;
    int len;
    char buffer [256];
    char * ptr = buffer;
    int maxLen = sizeof(buffer);
    struct sockaddr_in serverAddr; // server socket address

    // check argc and handle argv

    if(argc != 4)
    {
        printf("Error, three arguments are required");
        exit(1);
    }
    serverName = argv[1];
    serverPort = atoi(argv[2]);
    myString = argv[3];

    //create the remote(server) socket address

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, serverName,&serverAddr.sin_addr);     // server ip address
    serverAddr.sin_port = htons(serverPort);
    // create the socket
    if((s = socket(PF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("Error creating the socket");
        exit(1);
    }

    // connect to server

    if(connect(s,(struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Error connecting to the server");
        exit(1);
    }

    // data transfer

    bzero(buffer, 256);
    int p = send(s, myString,strlen(myString), 0);

    printf("%d", p);
    /*int count = 0;
    n = recv(s,ptr,maxLen,0);
    printf("got here\n");
    while(n > 0)
    {
        printf("%d\n",count);
        count++;
        ptr += n; // move the pointer
        maxLen -= n;// reduce max
        len += n;
        n = recv(s,ptr,maxLen,0);
    }
    
    //print and verify

    buffer[len] = '\0';
    printf("Echo stream reveived\n");
    fputs(buffer,stdout);
    */
    //close socket
    close(s);
    
    //exit normally
    exit(0);
}
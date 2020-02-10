
// Client side C/C++ program to demonstrate Socket programming with a string
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <sys/time.h>
#include <string.h> 
#define PORT 60019 
   
int main(int argc, char *argv[]) 
{ 
    int sock = 0;
    int n; 
    struct sockaddr_in serv_addr; 
    char *hello = argv[1];
    char buffer[256] = {0}; 
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    if(argc != 2)
    {
        printf("Two arguments are required!");
        exit(1);
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
   //using the loopback address for testing
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("message sent from client\n"); 
    int test;
    while((test = select(sock+1, &sock, NULL, NULL, &tv)) > 0)
    {
        n = recv( sock , buffer, sizeof(buffer),0); 
    }
    printf("%d", test);
    printf("%s\n",buffer ); 
    return 0; 
} 

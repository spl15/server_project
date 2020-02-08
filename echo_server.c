
// Server side C/C++ program to demonstrate Socket programming with a string
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 60019
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[256] = {0}; 
    char *hello = "Hello from server"; 
    char* ptr = buffer;
    int maxLen = sizeof(buffer);
    int len = 0;
    int n;
       
    // Creating socket 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
   
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
   for(;;)
   { 
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
             exit(EXIT_FAILURE); 
        } 
            
       n = recv( new_socket , buffer, sizeof(buffer), 0);
       // {
        //    perror("Error receiving");
       //     exit(1);
       // }
        
        //    ptr += n;
        // maxLen -=n;
        //   len += n;
        //   n = recv( new_socket , buffer, 1024, 0);
        

        printf("%s\n",buffer); 
        //retrieve file
        FILE* fileName;
        fileName = fopen(buffer, "r");
        if(fileName == NULL)
        {
            printf("file opened");
        }
        else
        {
            printf("file NOT opened!\n");
        }
        //process the file
        




        send(new_socket , hello , strlen(hello) , 0 ); 
        //printf("%d", k);
        printf("message sent from server\n");
   } 
    return 0; 
} 

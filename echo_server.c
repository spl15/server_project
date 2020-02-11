

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
    char buffer[4096] = {0}; 
   // char *hello = "Hello from server"; 
    char* ptr = buffer;
    int maxLen = sizeof(buffer);
    char* head = "HTTP/1.1 200 OK\r\n\r\n";
    char* notFound = "HTTP/1.1 404 FILE NOT FOUND\r\n\r\n";
   // int len = 0;
    //int n;
    //char* delim = "\r\n";
       
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
       
   // bind to socket
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    // listen for a connection
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
    printf("server running\n");
   for(;;)
   { 
       // accept the connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
             exit(EXIT_FAILURE); 
        } 

        // receive a request   
       recv( new_socket , buffer, sizeof(buffer), 0);
       //gets first token in string header(assumed to be GET)
        char* token = strtok(buffer," ");
        //gets the file name to be requested;
        token = strtok(NULL," ");
        token = token +1;
        //memset(buffer,0,sizeof(buffer));
        printf("%s\n", token);
        //printf("%s\n",buffer); 
        //retrieve file
        FILE* fileName;
        // reads a file whos name is specified by the token after first word(GET) seperated by space)
        fileName = fopen(token, "r");
       //memset(buffer, 0, maxLen);
        if(fileName != NULL)
        {
            printf("file opened\n");
            //find the file size to send.
            fseek(fileName, 0L, SEEK_END);
            int fielSize = (int)ftell(fileName);
            // send the file
            char temp[150];
            char cat[4000];
            while(fgets(temp, 150, fileName) != 0)
            {
                strcat(cat, temp[);
            }
            strcat(buffer, cat);
            send(new_socket , ptr , fielSize , 0 );
        }
        else
        {
            //do work here
            printf("file not found!\n");
            sprintf(buffer, "%s", notFound);
            send(new_socket , buffer , maxLen , 0);
        }
        //process the file

        close(new_socket);
        //clear the buffer
       // memset(buffer, 0, sizeof(buffer));
       

             
    
   } 
    return 0; 
} 

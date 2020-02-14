/*
 * Stephen Lamalie
 * COP4635
 * project 01
 * httpServer.c
 * 
 */

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 60019
int main(int argc, char const *argv[]) 
{ 
    // declare the stuff i will need
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[8000] = {0};
    int maxLen = sizeof(buffer);
    char head[] = "HTTP/1.1 200 OK\r\n\r\n";
    char notFound[] = "HTTP/1.1 450 File not available \r\n\r\n FILE NOT AVAILABLE!S";
    int headSize = sizeof(head) - 1;


       
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
       
        //prints the file name that its trying to gain access to
        printf("%s\n", token);
       
        //retrieve file
        FILE* fileName;
        // reads a file whos name is specified by the token after first word(GET) seperated by space)
        fileName = fopen(token, "rb");
      
        if(fileName != NULL)
        {
            printf("file opened\n");
            //find the file size to send.
            fseek(fileName, 0L, SEEK_END);
            int fileSize = (int)ftell(fileName);
	        rewind(fileName);
            //clear the buffer again
            memset(buffer,0,maxLen);
            //add the header first 
            sprintf(buffer,"%s", head);//EDIT
    
	        int i = 0;
	        int c;
           
            // send the file
            
	        for(i = 0;i < fileSize;i++)//EDIT
	        {
	            c = fgetc(fileName);
	            buffer[i + headSize] = c;//EDIT
	             
	        }

            send(new_socket , buffer , (fileSize + headSize) , 0 );//EDIT
            fclose(fileName);
        }
        else
        {
            //send the fiel not found header
            printf("file not found!\n");
            send(new_socket , notFound, (sizeof(notFound) - 2)  , 0);
        }
       
	    
        close(new_socket);
    
   } 
    return 0; 
} 


/*
 * Stephen Lamalie
 * COP4635
 * project 01
 * httpClient.c
 * 
 */

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h> 
#define PORT 60019 

   
int main(int argc, char *argv[]) 
{ 
    // declare the stuff i will need
    int n; 
    struct sockaddr_in serv_addr; 
    char buffer[8000] = {0}; 
    char file[64];
    char ipadd[64] = {0};
    int exitBool;
    

    char head[] = "HTTP/1.1 200 OK\r\n\r\n";
    printf("IP address of server: \n(Hint: use 127.0.0.1 for testing) ");
    fgets(buffer, 16, stdin);
    //gets the ip address and points to a spot in memory
    // just in case of the progranm runs again
    char* tok = strtok(buffer,"\n");
    printf("%s\n", tok);
   strcpy(ipadd, tok);
   //enter the client loop
   do
   {
       int sock = 0;
       if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
       { 
           printf("\n Socket creation error \n"); 
           return -1; 
       } 
   
       serv_addr.sin_family = AF_INET; 
       serv_addr.sin_port = htons(PORT); 
    
   
       if(inet_pton(AF_INET, ipadd, &serv_addr.sin_addr)<=0)  
       { 
           printf("\nInvalid address/ Address not supported \n"); 
           return -1; 
       } 
   
       if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
       { 
           printf("\nConnection Failed \n"); 
           return -1; 
       } 
    
       exitBool = 1;
       printf("Please enter the file name: \n(Hint: remember to use the path, it should start with /) \n");
       fgets(file, 64, stdin);
       char* toke = strtok(file, "\n");

       //put a simple get request in the buffer with the file to get and a blank line after
       sprintf(buffer, "GET %s HTTP/1.1\r\nHost: 127.0.0.1:600019\r\n", toke);
       
       //send the get request in the buffer
       send(sock , buffer , sizeof(buffer), 0 ); 
       printf("request sent from client\n"); 
    
    
    
       if((n = recv(sock , buffer, sizeof(buffer),0)) < 0)
       {
           perror("Error receiving");
           exit(1);
       } 
    
        //checks to see if the 200 OK header was sent back, creates a file if so
       char* token = strtok(buffer, "\n");
       if(strncmp(token, head, 15) == 0)
       {
           printf("File received\n");
           FILE* theFile;
            // create a file with the contents of the buffer
           theFile = fopen("new_file.txt", "w+");
           int i = 0;
           char c;

           for(i = 0;i < (n - sizeof(head));i++)
           {
     
	           c = buffer[i + sizeof(head)-1];
	           fputc(c, theFile);
            
           }
        //close the file
        fclose(theFile);
    }
    else
    {
        // if 200 OK header was not sent back it only displays the header to find what went wrong
        printf("%s\n", token);
    }
    //giving the user a chance tyo exit the loop
    printf("Press (x) to exit, enter any other single character key to process another request \n");
    fgets(buffer, 16, stdin);

    char* tokenn = strtok(buffer, "\n");
    if((strcmp(tokenn, "x")) == 0)
    {
        exitBool = 0;
    }

    // socket needs to be closed every use, create a new one if need be...
    close(sock);
    
    
    }while(exitBool);
    

  
    return 0; 
} 

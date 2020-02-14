

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
    
    int n; 
    struct sockaddr_in serv_addr; 
    char buffer[8000] = {0}; 
    char file[64];
    char ipadd[64] = {0};
    int exitBool;
    

    char head[] = "HTTP/1.1 200 OK\r\n\r\n";
    printf("IP address of server: \n(Hint: use 127.0.0.1 for testing) ");
    fgets(buffer, 16, stdin);
    char* tok = strtok(buffer,"\n");
    printf("%s\n", tok);
   strcpy(ipadd, tok);
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
    
   //do
   //{
    if(inet_pton(AF_INET, ipadd, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   //do
   //{
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
    //clear the buffer with 0's
    
    
    if((n = recv(sock , buffer, sizeof(buffer),0)) < 0)
    {
        perror("Error receiving");
        exit(1);
    } 
    //printf("%s\n",buffer ); 
    //write what is received to a file
    
    char* token = strtok(buffer, "\n");
    if(strncmp(token, head, 15) == 0)
    {
        printf("File received\n");
        FILE* theFile;
    
        theFile = fopen("new_file.txt", "w+");
    
        //fwrite(buffer, 1, sizeof(buffer),theFile);
        int i = 0;
        char c;
        //printf("%d", n);
        for(i = 0;i < (n - sizeof(head));i++)
        {
     
	        c = buffer[i + sizeof(head)-1];
	        fputc(c, theFile);
            
        }
    
        fclose(theFile);
    }
    else
    {
        printf("%s\n", token);
    }
    printf("Press (x) to exit, enter any other single character key to process another request \n");
    fgets(buffer, 16, stdin);
    //char c = fgetc(stdin);
    char* tokenn = strtok(buffer, "\n");
    if((strcmp(tokenn, "x")) == 0)
    {
        exitBool = 0;
    }


    close(sock);
    
    
    }while(exitBool);
    

  
    return 0; 
} 

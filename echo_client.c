

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
    int sock = 0;
    int n; 
    struct sockaddr_in serv_addr; 
    char buffer[1024]; 
    char *ptr = buffer;
    //char* delim = "\r\n";

    if(argc != 2)
    {
        printf("Two arguments are required!\n One for the executable and one for the file requested.");
        return -1;
    }
    char *hello = argv[1];
   
    
    int maxLen = sizeof(buffer);
    int len = 0;
   // struct timeval tv;
   // tv.tv_sec = 2;
  // tv.tv_usec = 0;

    if(argc != 2)
    {
        printf("Two arguments are required!");
        return -1;
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

    //put a simple get request in the buffer with the file to get and a blank line after
    sprintf(buffer, "GET %s HTTP/1.1\r\nHost: 127.0.0.1:600019\r\n", argv[1]);
    //send the get request in the buffer
    send(sock , buffer , sizeof(buffer), 0 ); 
    printf("request sent from client\n"); 
    //clear the buffer with 0's
    //memset(ptr,0, sizeof(buffer));
    
    if((n = recv(sock , buffer, sizeof(buffer),0)) < 0)
    {
        perror("Error receiving");
        exit(1);
    } 
    //printf("%s\n",buffer ); 
    //write what is received to a file
    FILE* theFile;
    
    theFile = fopen("new_file.txt", "w+");
    //fwrite(buffer, 1, sizeof(buffer),theFile);
    int i;
    char c;
    for(i = 0;i < maxLen;i++)
    {
	c = buffer[i];
	//fputc(c, theFile);
	if(c == EOF)
	{
	    break;
	}
        else
	{
            fputc(c ,theFile);
	}
    }
    fclose(theFile);
    close(sock);

  

  
    return 0; 
} 

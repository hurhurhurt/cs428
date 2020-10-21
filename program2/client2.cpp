#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include<iostream>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <cmath>

using namespace std;
#define MAX 80 
#define PORT 12000 
  
// Driver code 
int main() { 
    int sockfd;
    struct sockaddr_in servaddr; 

    // Creating UDP socket file descriptor; SOCK_DGRAM used for UDP packets.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }   
    else
        printf("Socket successfully created..\n"); 
   

    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);  

    // The connect() system call initiates a connection on a socket
    int conn_obj = connect(sockfd, (const sockaddr*) &servaddr, sizeof(servaddr));
    
    // if the returned object is not zero, failure!
    if(conn_obj !=0){
        printf("connection with the server failed...\n"); 
        exit(0); 
    } // else sucess in connection
    else
        printf("connected to the server..\n"); 
    
    // takes appropriate message from client 2
    char client_message[256] = "This is the message from Client Y: Bob";
    
    // sends to the server socket
    send(sockfd, client_message, sizeof(client_message), 0);
    
    // holds server response
    char server_response[256];
    
    //The recv() function shall return the length of the message written to the buffer pointed to by the buffer argument.
    recv(sockfd, &server_response, sizeof(server_response), 0);
    printf("\n** Message sent to the Server ** \n%s\n", client_message);
    printf("\n** Acknowledgement from Server ** \n%s\n", server_response);
  
    // close the socket 
    printf("\n\n");
    close(sockfd); 
    return 0;
}

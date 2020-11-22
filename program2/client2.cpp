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
#define MESSAGESIZE 1000 
#define PORT 12000 
  
// Driver code 
int main() { 
    int sockfd;
    struct sockaddr_in servaddr; 

    // Create TCP Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { 
      cout << "socket unable to be made " << endl; 
      exit(1); 
    }   
    else{
      cout << "socket created!" << endl;
    }
   
    // Fill server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);  

    // The connect() system call initiates a connection on a socket
    int socket_connection = connect(sockfd, (const sockaddr*) &servaddr, sizeof(servaddr));
    if (socket_connection !=0){
      cout << "connection failed" << endl;
      exit(1);
    }
    else{
      cout << "connected to server successfully" << endl;
    }
    
    // Client 2 Message
    char client_message[MESSAGESIZE] = "This is the message from Client Y: Bob";
    
    // Sends client_message to server
    send(sockfd, client_message, sizeof(client_message), 0);
    
    char server_response[MESSAGESIZE];
    
    // Gets the response from the server using the recv() call and store in server_response
    recv(sockfd, &server_response, sizeof(server_response), 0);
    cout << endl << "Message sent to the server: " << endl << client_message << endl;
    cout << endl << "Acknowledgement from Server: " << endl << server_response << endl;
    
    // Close socket
    close(sockfd); 
    return 0;
}

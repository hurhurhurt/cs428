#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

#define MESSAGESIZE 1000
#define PORT 12000
using namespace std;

int main() { 
	int sockfd, connfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr;

	// Create a TCP socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
       	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // localhost
	servaddr.sin_port = htons(PORT); // port number

	// Bind the socket with the server address
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

	// Server waits for clients 1 and 2
	listen(sockfd, 5);
	
	// Hold the messages from clients 1 and 2
	char client_message1[MESSAGESIZE];
	char client_message2[MESSAGESIZE];
	int client_socket1, client_socket2;
	cout << "Waiting..." << endl;

	// Accepts the connection requests for each socket
	client_socket1 = accept(sockfd, NULL, NULL);
	client_socket2 = accept(sockfd, NULL, NULL);

	// Gets each respective client message and stores in proper variables
	recv(client_socket1, &client_message1, sizeof(client_message1), 0);
	recv(client_socket2, &client_message2, sizeof(client_message2), 0);

	// Print the respective messages to stdout
	cout << ("\nClient Messages: ") << endl;
	cout << client_message1 << endl;
	cout << client_message2 << endl;

	// ack is to let clients know that they received the message, first is which message got to server first
	static char ack[MESSAGESIZE];
	char *first = NULL;
	
        // If first message is from Alice, acknowledge it first. Else, acknowledge Bob's message.
	first = strstr(client_message1 , "Alice");
	
	if (first) {
	  strcpy(ack, "X: Alice received before Y: Bob");
	}
	else{
	  strcpy(ack, "Y: Bob received before X: Alice");
	}
	
	// Server sends acknowledgements to both clients
	send(client_socket1, ack, sizeof(ack), 0);
	send(client_socket2, ack, sizeof(ack), 0);
	cout << "\nAcknowledgments sent to both clients" << endl;
	
	// Closes the socket
	close(sockfd);
	return 0;
} 

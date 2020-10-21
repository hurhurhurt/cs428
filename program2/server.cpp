#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define MAX 80 
#define PORT 12000
using std::string;

// Driver function
int main() { 

	int sockfd, connfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cli; 
	
    // Here we create the Socket, sockfd: Socket decriptor, an integer
	// new socket(Domain, Type, Protocol), where arguments-
	// Domain : AF_INET(IPv4 protocol), AF_INET6(IPv6 protocol)
	// Type : SOCK_DGRAM (for UDP), SOCK_STREAM(TCP)
	// Protocol: 0 (default Protocol val)
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    // if val is zero, failure!
	if (sockfd < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }   

    else{
        printf("Socket successfully created..\n");
    }
	
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // localhost
	servaddr.sin_port = htons(PORT); // port number
	
    // Here we BIND the new created socket object i.e. sockfd with the server address
	// bind(socketobj, servaddr, servaddrlen), where arguments-
	// socketobj: sockfd
	// servaddr: server address for the sockfd to be binded to
	// servaddrlen: server address structure size
	int return_val = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	
    // if returned val is negative, failure!
    if(return_val < 0){
		perror("bind failed"); 
        exit(EXIT_FAILURE);
	}
	else{
        printf("Socket successfully binded..\n");
        }
	
	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else{
		printf("Server is listening..\n");
	}

    // Hold the messages from client 1 and 2 respectively
	char client_message1[128];
    char client_message2[128];

	int client_socket1, client_socket2;
    puts("Waiting for clients...");


    // The accept() function takes the following arguments:
    // socket object: Specifies a socket that was created with socket(), has been bound to an address with bind(), and has issued a successful call to listen().
    // address: Either a null pointer, or a pointer to a sockaddr structure where the address of the connecting socket shall be returned.
    // address_len : Points to a socklen_t structure which on input specifies the length of the supplied sockaddr structure, and on output specifies the length of the stored address.
	client_socket1 = accept(sockfd, NULL, NULL);
	client_socket2 = accept(sockfd, NULL, NULL);

    //The recv() function shall return the length of the message written to the buffer pointed to by the buffer argument.
	recv(client_socket1, &client_message1, sizeof(client_message1), 0);
	recv(client_socket2, &client_message2, sizeof(client_message2), 0);

    printf("\n** Messages Received from clients **\n");
	printf("%s\n", client_message1);
	printf("%s\n", client_message2);

    static char message[128];
    char *output = NULL;
    
    // TO CHECK THE ORDER of message sent by clients
    // If client message1 contains "X" that means client 1 i.e. X sent the message first
    // else client 2 i.e. "Y" did
    // This "strstr" function takes two strings s1 and s2 as an argument and finds the first occurrence 
    // of the sub-string s2 in the string s1
    output = strstr(client_message1,"X");

    // if there is an occurence, X sent first
    if(output) {
        strcpy(message, "X: Alice received before Y: Bob");
    }

    // else
    else{
        strcpy(message, "Y: Bob received before X: Alice");
    }

    // the server responds to both the clients and send
    // the respective acknowledgment
	send(client_socket1, message, sizeof(message), 0);
    send(client_socket2, message, sizeof(message), 0);
    printf("\nSent acknowledgment to both X and Y! \n");
    printf("\n\n");
	
    // closes the socket object! job done!
    close(sockfd);
	return 0;
} 

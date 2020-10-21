// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <chrono>
#include <iostream>

#define PORT    20000
#define MAXLINE 1024

// Driver code
int main() {
  int sockfd, n;
  char buffer[MAXLINE];
  struct sockaddr_in     servaddr, cliaddr;

  // Create a socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // Flush data
  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // FIll server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Declare variables len (length of the sockaddr structure pointed to by servaddr and the message hello
  socklen_t len;
  char hello[] = "hello there!";

  // Declare timeval struct for use in setting a timeout, set timeout to 1 sec
  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;

  // setockopt() with the SO_RCVTIMEO option will set a timeout of 1 second
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv));

  // Loop 10 times as specified in project instructions
  for (int i = 0; i < 10; i++){
    // Declare current time before function message is sent
    auto start = std::chrono::system_clock::now();

    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr,
	   sizeof(servaddr));

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,
    		 &len);

    // Calculate time after message is both sent and received (aka RTT)
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    // If time < seconds, no timeout occurred
    if (elapsed_seconds.count() < 1) { 
      std::cout<< "elapsed_time: " << elapsed_seconds.count() << "s\n";
    }
    // Otherwise a timeout occured and we note it
    else printf("Timeout occured!\n");
       
    // Flush buffer
    buffer[n] = '\0';
    
    // Below code for debugging purposes (message is properly received in buffer)
    // printf("Server : %s\n", buffer);
  }
  
  close(sockfd);
  return 0;
} 

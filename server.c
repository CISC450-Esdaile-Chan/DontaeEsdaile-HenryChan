#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>

typedef struct datagram {
    unsigned char header[4];
    char data[80];
}DatagramSegment;

DatagramSegment packet;

int main(int argc, char *argv[]) {

    short count;
    short sequence_number;


    // Socket descriptor
	int sockfd;
	struct sockaddr_in	servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize socket
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;      
    servaddr.sin_port = htons(9090);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
    // Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    int len = sizeof(cliaddr);

    recvfrom(sockfd, (DatagramSegment *)&packet, sizeof(packet),
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
    
  printf("client filename: %d", packet.header[0]);
  printf("Never gets here");


    close(sockfd);
    return 0;
}
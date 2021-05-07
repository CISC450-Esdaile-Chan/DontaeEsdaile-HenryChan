#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void construct_datagram(int socket, const struct sockaddr * servaddr, socklen_t len,  short count, short sequence_number, char data);

int simulate_ackloss(double acklr);

typedef struct datagram {
    unsigned char header[4];
    char data[80];
}DatagramSegment;

DatagramSegment packet;

int main(int argc, char *argv[]) {

    short count;
    short sequence_number;

    char filename[80];
	printf("Enter file name: ");
	scanf("%s", &filename);


    // Socket descriptor
	int sockfd;
	struct sockaddr_in	servaddr, cliaddr;
    
    int server_len = sizeof(servaddr); 

    // Initialize socket
    servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9090);
	servaddr.sin_addr.s_addr = ("127.0.0.1");


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("Failed to create a socket");
		exit(EXIT_FAILURE);
	}

    // clear memory
    memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

    construct_datagram(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr), 100, 1, filename);


    close(sockfd);
}

void construct_datagram(int socket, const struct sockaddr * servaddr, socklen_t len, short count, short sequence_number, char data){
    // Construct datagram
    packet.header[0] = count;
    packet.header[1] = count >> 8;
    packet.header[2] = sequence_number;
    packet.header[3] = sequence_number >> 8;
    packet.data[80] = data;

    sendto(socket, (void *)&packet, sizeof(packet), MSG_CONFIRM, servaddr, len);
    //send(sockid, (void *)&packet, sizeof(packet), 0);
}

/*
int simulate_ackloss(double acklr){
	time_t t;
    
    srand((unsigned) time(&t));
	int loss = rand() % 99;
	for(int j = 0; j < n; j++){
		if(loss < acklr){
			return 1;
		} else {
			return 0;
		}
    }
    return 0;
}*/



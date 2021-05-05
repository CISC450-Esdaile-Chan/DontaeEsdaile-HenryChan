// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <binn.h>

#define PORT	 9090
#define MAXLINE 1024


// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);

	/*
    char line_buffer[80];
    FILE* file;
	file= fopen(buffer, "r"); // read file with name buffer
    fgets(line_buffer, sizeof(line_buffer), file);

	sendto(sockfd, (const char *)line_buffer, strlen(line_buffer),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	*/
	


	// binn test area

	binn *obj;

	obj = binn_object();

	binn_object_set_int32(obj, "id", 123);
	binn_object_set_str(obj, "name", "John");
	binn_object_set_double(obj, "total", 2.55);


	// send over the network or save to a file...
	//send(sock, binn_ptr(obj), binn_size(obj));
	sendto(socket, binn_ptr(obj), binn_size(obj),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

	// release the buffer
	binn_free(obj);

	return 0;
}
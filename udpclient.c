// Client side implementation of UDP client-server model
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

    char client_filename[256];
	printf("Enter file name: ");
	scanf("%s", &client_filename);

	int sockfd;
	char buffer[80];
	struct sockaddr_in	servaddr;

    
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	
	int n, len;
	
    len = sizeof(servaddr);

	sendto(sockfd, (const char *)client_filename, strlen(client_filename),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("File name sent.\n");

	/*	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);
	*/



	//binn area

	int id;
	char *name;
	double total;

	binn *server_responce;

	recvfrom(sockfd, binn_ptr(server_responce), binn_size(server_responce) , 0, (struct sockaddr *) &servaddr, len);


	id = binn_object_int32(server_responce, "id");
	name = binn_object_str(server_responce, "name");
	total = binn_object_double(server_responce, "total");
	printf("Server : %s", name);

	binn_free(server_responce);

	close(sockfd);
	return 0;
}
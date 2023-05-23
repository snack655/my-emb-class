#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define UDP_PORT 5100

int main(int argc, char **argv) {
	int sockfd, n;
	socklen_t clisize;
	struct sockaddr_in servaddr, cliaddr;
	char mesg[BUFSIZ];

	if(argc != 2) {
		printf("usage : %s <IP address>\n", argv[0]);
		return -1;
	}


/*
	This is a common model for tcp connction. -
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "http_parser.h"

struct tcp_config
{
	int domain;
	int type;
	int protocol;
};

void http(
	struct sockaddr_in server_addr,
	struct tcp_config tcp_config,
	void (*tcp_processor)(char*)
) {
	struct sockaddr_in client_address;
	int server_sockfd, client_sockfd;
	int client_len;
	int server_len;

	int tcp_domain = AF_INET;
	int tcp_type = SOCK_STREAM;
	int tcp_protocol = 0;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_len = sizeof(server_address);

	unlink("server_socket");
	server_sockfd = socket(
		tcp_config.domain,
		tcp_config.type,
		tcp_config.protocol
	);

	bind(
		server_sockfd,
		(struct sockaddr *)&server_address,
		sizeof(server_addr)
	);

	listen(server_sockfd, 5);
	printf("server listening on port %d.\n", port);

	char ch;
	client_len = sizeof(client_address);
	client_sockfd = accept(
		server_sockfd,
		(struct sockaddr *)&client_address,
		&client_len
	);

	while (1)
	{
		read(client_sockfd, ch, 1);
		http_request_parser(ch);
	}

	write(client_sockfd, &ch, 1);

	close(client_sockfd);

	
}




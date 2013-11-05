#include <stdio.h>
#include "tcp_socket.h"

void test1(char* ch)
{
	*ch = *ch + 2;
}

int main(int argc, char* argv)
{
	const char* ip = "127.0.0.1";
	unsigned int port = 8080;

	tcp_socket(ip, port, test1);

	return 0;
}




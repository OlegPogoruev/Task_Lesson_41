


#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <arpa/inet.h>


#include <stdio.h>
#include <string.h>

#define CLIENT "224.0.0.88"

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data



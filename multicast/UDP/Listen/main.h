
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

//#define SERVER "127.0.0.1"
//#define SERVER "194.55.44.1"
//#define SERVER "192.168.192.255"
//#define SERVER "192.168.192.128"
#define GROUP "224.0.0.88"


#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to send data



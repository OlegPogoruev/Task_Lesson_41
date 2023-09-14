
#include "main.h"


void get_input_string(char *str_in);


int main(void)
{
	struct sockaddr_in sock_client;		// initilaize struct of socket
	int fd;					// deskriptor socket
	int slen;				// len structure socket
	char buf[BUFLEN];
	int recv_len;				// len received mesage
	
	if ( (fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){perror("can't socket");return -1;}
	
	
        int temp = 1;
        if( (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &temp, sizeof(temp)) ) != 0){perror("can't option setsockopt"); return(-1);}
        
	/////////////////////////////////////////////////////
	// zero out the structure
	memset((char *) &sock_client, 0, sizeof(sock_client));
	slen = sizeof(sock_client);				// len structure socket
	// init structure
	sock_client.sin_family = AF_INET;
	sock_client.sin_port = htons(PORT);
	sock_client.sin_addr.s_addr = htonl(INADDR_ANY);
	/////////////////////////////////////////////////////
	
	//bind socket to port
	if( bind(fd , (struct sockaddr*)&sock_client, sizeof(sock_client) ) == -1){perror("can't open bind");return(-1);}

	while(1)
	{
		if ((recv_len = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *) &sock_client, &slen)) == -1){perror("can't recvfrom()");return -1;}
		buf[recv_len] = 0;
		printf("Received packet from %s:%d\n", inet_ntoa(sock_client.sin_addr), ntohs(sock_client.sin_port));
		printf("Data: %s\n" , buf);
		if (strcmp (buf, "exit")==0){break;}
	}

	close(fd);
	return 0;
}



void get_input_string(char *str_in)
{
    int ch = 0;
    int temp_count = 0;
    while ((ch = getchar()) != '\n')
    {
        (*(str_in + temp_count)) = ch;
        ++temp_count;
        if(temp_count > (BUFLEN - 2 ))
        {
//          (*(str_in + temp_count)) = '\n';
//          ++temp_count;
          break;
        }
    }
//    (*(str_in + temp_count)) = '\n';
    (*(str_in + temp_count)) = 0;    
}





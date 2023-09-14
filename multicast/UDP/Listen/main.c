
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
	
	// set enable back loop, control data future sended in local interfeise back loop
        int temp = 1;
        if( (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, &temp, sizeof(temp)) ) != 0){perror("can't option setsockopt"); return(-1);}
	
	
	
        struct ip_mreq mreq;                            // init structure multicast
        mreq.imr_multiaddr.s_addr = inet_addr(GROUP);   // Set IP-adres group multicast, similar to creating a group QQ
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);	// Add this computer in group multcast, similar to adding a group
//	mreq.imr_ifindex = 0;
	
	// Set option socket and join multicast group
	if( (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) ) < 0){perror("can't option setsockopt"); return(-1);}
	


	while(1)
	{
		if ((recv_len = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *) &sock_client, &slen)) == -1){perror("can't recvfrom()");return -1;}
		buf[recv_len] = 0;
		printf("Received packet from %s:%d\n", inet_ntoa(sock_client.sin_addr), ntohs(sock_client.sin_port));
		printf("Data: %s\n" , buf);
		if (strcmp (buf, "exit")==0){break;}
	}
        
        // Set socket options and leave multicast group
        if( (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) ) < 0){perror("can't leave setsockopt"); return(-1);}
        
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





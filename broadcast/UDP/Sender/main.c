
#include "main.h"

void revers_string(char *str);

void get_input_string(char *str_in);



int main(void)
{
	int size;
	struct sockaddr_in sock_serv, sock_client;		// initilaize struct of socket
	int fd;							// deskriptor socket
	int slen;						// len structure socket
	int recv_len;						// len received mesage
	
	char buf[BUFLEN];
	
	//create a UDP socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){perror("can't open socket");return(-1);}
	
	/////////////////////////////////////////////////////
	// zero out the structure
	memset((char *) &sock_serv, 0, sizeof(sock_serv));
	// init structure
	sock_serv.sin_family = AF_INET;
	sock_serv.sin_port = htons(PORT);
	sock_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	/////////////////////////////////////////////////////
	// zero out the structure
	memset((char *) &sock_client, 0, sizeof(sock_serv));
	slen = sizeof(sock_client);				// len structure socket
	sock_client.sin_family = AF_INET;
	sock_client.sin_port = htons(PORT);
//	sock_client.sin_addr.s_addr = htonl(INADDR_ANY);
        if (inet_aton(CLIENT , &sock_client.sin_addr) == 0){fprintf(stderr, "inet_aton() failed\n");return -1;}
	/////////////////////////////////////////////////////
	
        int temp = 1;
	if( (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &temp, sizeof(temp)) ) != 0){perror("can't option setsockopt"); return(-1);}
	
	//keep listening for data
	while(1)
	{
            printf("Enter message : ");
            get_input_string(buf);
            
            //now reply the client with the same data
            printf("Data: %s\n" , buf);
            if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr*) &sock_client, slen) == -1){perror("can't sendto()");return(-1);}
            
            if (strcmp (buf, "exit")==0){break;}
	}

	close(fd);
	return 0;
}


void revers_string(char *str)
{

	char temp_str[BUFLEN];
	int i = 0;
	int j = 0;
	while(0 != (*(str + i))){++i;}
	while(0 != i)
	{
	    --i;
	    temp_str[j] = (*(str + i));
	    ++j;
	}
	temp_str[j] = 0;
	strncpy (str, temp_str,BUFLEN);
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








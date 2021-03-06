#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define LIMIT 1000

int main(int argc, char* argv[])
{
	int ip_ind = 2;
	if (argc < ip_ind) {
		printf("\n\tusage: ./device file.txt [ip]\n");
		return 1;
	}

    int sockfd;
    int bytes_length = 0, check = 1;
    char checkarr[2];
    struct sockaddr_in server_addr;
    char send_data[1024];
    struct hostent *host = (struct hostent *)gethostbyname((argc > ip_ind) ? argv[ip_ind] : "localhost");
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);
	
/*
	FILE *f;
    f = fopen(argv[1],"r");		// open file given in terminal, read
	int bytes_read;
    while (!feof(f))
        bytes_read = fread(&send_data,1,sizeof(send_data),f);
*/
	//add receive line
	bytes_length = recvfrom(sockfd,recv_data,1024,0, (struct sockaddr *)&server_addr, &addr_len);
	bool freturn = firewall(recv_data, LIMIT);
	if(freturn){
		check = 1;
		sprintf(checkarr, "%d", check)
		sendto(sockfd, checkarr, bytes_length, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	}
	else{
		check = 0;
		sprintf(checkarr, "%d", check)
		sendto(sockfd, checkarr, bytes_length, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	}
	// authentication
	// receive authentication number
	// runs firewall on that authentication number
	// disconnect if blocked by firewall
	
	//sendto(sockfd, send_data, bytes_read, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    //fclose(f);

    return 0;
}

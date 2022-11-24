
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<linux/if_packet.h>
#include<netinet/in.h>		 
#include<netinet/if_ether.h>    // for ethernet header
#include<netinet/ip.h>		// for ip header
#include<netinet/udp.h>		// for udp header
#include<netinet/tcp.h>
#include<arpa/inet.h>           // to avoid warning at inet_ntoa

#include<wiringSerial.h>


#define BAUD 9600

struct sockaddr saddr;
struct sockaddr_in source,dest;

void recv_data_process(unsigned char* buffer,int buflen);
int fd;

int main()
{

	int sock_recv,saddr_len,buflen;

	unsigned char* buffer = (unsigned char *)malloc(65536); 
	memset(buffer,0,65536);
	
	if((fd = serialOpen("/dev/ttyACM1", 9600)) < 0) {
		printf("file open error");
		return 1;
	}

	printf("starting .... \n");

	sock_recv=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)); 
	if(sock_recv<0)
	{
		printf("error in socket\n");
		return -1;
	}

	while(1)
	{
		saddr_len=sizeof saddr;
		buflen=recvfrom(sock_recv,buffer,65536,0,&saddr,(socklen_t *)&saddr_len);

		if(buflen<0)
		{
			printf("error in reading recvfrom function\n");
			return -1;
		}

		//---------------------------------------
		recv_data_process(buffer,buflen);
		//---------------------------------------
	}

	close(sock_recv);// use signals to close socket 
	printf("DONE!!!!\n");
}


//================================================================


void recv_data_process(unsigned char* buffer,int buflen)
{
	
	char str[3];
	int j = 0;
	if(buffer[0] == 0xFC && buffer[1] == 0xB3 && buffer[2] == 0xBC && buffer[3] == 0x4B && buffer[4] == 0xEA && buffer[5] == 0x24)
	{
		for(int i=42; i<45; i++) {
			printf("%c", buffer[i]);
			str[j] = buffer[i];
			j++;
		}
		printf("%s", str);
		serialPuts(fd, str);
		serialFlush(fd);
		j = 0;
		printf("\n");
					
	}

}

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<errno.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>

#include<net/if.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<netinet/udp.h>

#include<linux/if_packet.h>

#include<arpa/inet.h>

#include<unistd.h>


struct ifreq ifreq_i;
int sock_raw;
unsigned char *sendbuff;
int total_len=0,send_len;

struct sockaddr_ll sadr_ll;

void send_data_process();

//--------------------------------
char *eth_dev_name = "ens33";
int buff_len = 64;
//--------------------------------

void get_eth_index()
{
	memset(&ifreq_i,0,sizeof(ifreq_i));
	strncpy(ifreq_i.ifr_name,eth_dev_name,IFNAMSIZ-1);

	if((ioctl(sock_raw,SIOCGIFINDEX,&ifreq_i))<0)
		printf("error in index ioctl reading");

	printf("index=%d\n",ifreq_i.ifr_ifindex);
}

int send_net(unsigned char *sendbuff, int buff_len)
{
	int send_len = 0;
	send_len = sendto(sock_raw,sendbuff,buff_len,0,(const struct sockaddr*)&sadr_ll,sizeof(struct sockaddr_ll));
	return send_len;
}


int count = 0;

int main()
{
	sock_raw=socket(AF_PACKET,SOCK_RAW,IPPROTO_RAW);
	if(sock_raw == -1)
		printf("error in socket");

	sendbuff=(unsigned char*)malloc(buff_len); // increase in case of large data.Here data is --> AA  BB  CC  DD  EE
	memset(sendbuff,0,buff_len);

	get_eth_index();  // interface number

	sadr_ll.sll_ifindex = ifreq_i.ifr_ifindex;
	sadr_ll.sll_halen   = ETH_ALEN;

	send_data_process();
}

//===========================================================


unsigned short checksum(unsigned short* buff, int len_16)
{
	unsigned long sum = 0;

	for(int i = 0;i < len_16;i++)
		sum+=htons(*(buff)++);	
	do
	{
		sum = ((sum >> 16) + (sum & 0xFFFF));
	}
	while(sum & 0xFFFF0000);

	return (~sum);
}


void buff_init()
{
	
	// 00:0c:29:36:ec:29 / window : FC-B3-BC-4B-EA-24
	sendbuff[0]  = 0xFC;
	sendbuff[1]  = 0xB3;
	sendbuff[2]  = 0xBC;
	sendbuff[3]  = 0x4B;
	sendbuff[4]  = 0xEA;
	sendbuff[5]  = 0x24;	
	// Source MAC Address : 00:0c:29:92:6a:6c
	sendbuff[6]  = 0x06;
	sendbuff[7]  = 0x07;
	sendbuff[8]  = 0x08;
	sendbuff[9]  = 0x09;
	sendbuff[10]  = 0x0a;
	sendbuff[11]  = 18;  // 100 : 샘거
	// Type = ARP : 0x0806, IP : 0x0800
	sendbuff[12]  = 0x08;
	sendbuff[13]  = 0x00;

	//----------------------------------------
	// IP Header
	//sendbuff[14] = (4 << 4) | 5; // Version : 4, Head Length : 5*4 = 20
	sendbuff[14] = 0x45;
	sendbuff[15] = 0x00;  // TOS
	sendbuff[16] = 0;  // Total Length
	sendbuff[17] = 64 - 14;
	sendbuff[18] = 0;  // ID
	sendbuff[19] = 0;	
	sendbuff[20] = 0;  //  Flags, Fragment Offset
	sendbuff[21] = 0;	
	sendbuff[22] = 64;	// TTL
	sendbuff[23] = 17;  // Protocol : 6-TCP, 17-UDP
	sendbuff[24] = 0;  // Header Checksum
	sendbuff[25] = 0;		
	sendbuff[26] = 192;   // Source IP
	sendbuff[27] = 168;
	sendbuff[28] = 71;
	sendbuff[29] = 129;
	sendbuff[30] = 192;   // Destination IP
	sendbuff[31] = 168;
	sendbuff[32] = 71;
	sendbuff[33] = 129;

	// IP Header Checksum
	unsigned short header_checksum = checksum((unsigned short*)(&sendbuff[14]), 20/2);  // 20 bytes
	sendbuff[24] = (header_checksum & 0xff00) >> 8;
	sendbuff[25] = header_checksum & 0xff;

	//-----------------------------------------
	// UDP Header
	sendbuff[34] = (10005 & 0xff00) >> 8;  // Source Protocol																																																									
	sendbuff[35] = 10005 & 0xff;	
	sendbuff[36] = (10000 & 0xff00) >> 8;  //Destination Port
	sendbuff[37] = 10000 & 0xff;
	sendbuff[38] = 0;  //Total Length
	sendbuff[39] = 64 - 14 - 20;  // total : 64, ethernet : 14, IP : 20
	sendbuff[40] = 0;  // Checksum
	sendbuff[41] = 0;	

	//------------------------------------------
	// user Data
	sendbuff[42] = '1';
	sendbuff[43] = 'o';	
	sendbuff[44] = 'n';

}



void send_data_process()
{

	// unsigned int a = 0x12345678;
	// char *b = &a;
	// printf("%02x..\n", *b);


	buff_init();

	printf("sending...\n");
	int mode = 0; // 0 1 2 3
	while(1)
	{
		if(mode == 0) {
			sendbuff[42] = '1';
			sendbuff[43] = 'o';
			sendbuff[44] = 'n';
		} else if (mode == 1) {
			sendbuff[42] = '1';
			sendbuff[43] = 'o';
			sendbuff[44] = 'f';
		} else if (mode == 2) {
			sendbuff[42] = '2';
			sendbuff[43] = 'o';
			sendbuff[44] = 'n';

		} else if (mode == 3) {
			sendbuff[42] = '2';
			sendbuff[43] = 'o';
			sendbuff[44] = 'f';
		}
		mode++;
		if(mode > 3) {
			mode = 0;
		}
		send_len = send_net(sendbuff, buff_len);
		if(send_len<0)
		{
			printf("sendlen=%d....errno=%d\n",send_len,errno);
			return -1;
		}

		printf("count = %d\n", count++);
		usleep(1000000);
	}
}

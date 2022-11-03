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
#include<netinet/tcp.h>

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

total_len = 64 - 14 - 20;

unsigned short tcp_udp_checksum(unsigned short* buff, int len_per_16bit, unsigned short* pseudo_header, int pseudo_len_per_16bit)
{
	unsigned long sum = 0;
	for(int i = 0;i < len_per_16bit;i++)
		sum+=htons(*(buff)++);

	for(int i = 0;i < pseudo_len_per_16bit;i++)
		sum+=htons(*(pseudo_header)++);

	do
	{
		sum = ((sum >> 16) + (sum & 0xFFFF));
	}
	while(sum & 0xFFFF0000);

	return (~sum);
}

struct tcp_pseudo_header{
	unsigned int source_ip;
	unsigned int dest_ip;
	unsigned char reserved;
	unsigned char protocol;
	unsigned short tcp_length;
};
struct tcp_pseudo_header pseudo_header; 

unsigned short tcp_checksum()
{
	int tcp_length = total_len - (sizeof(struct ethhdr) + sizeof(struct iphdr));
	unsigned short *tcp_buffer = (unsigned short*)(sendbuff + sizeof(struct ethhdr) + sizeof(struct iphdr));

	struct tcp_pseudo_header *pseudo_buffer = (struct tcp_pseudo_header *)&pseudo_header;
	pseudo_buffer->source_ip = (unsigned int)iph->saddr;
	pseudo_buffer->dest_ip = (unsigned int)iph->daddr;
	pseudo_buffer->reserved = 0;
	pseudo_buffer->protocol = (unsigned char)iph->protocol;   // udp:6, tcp:17
	pseudo_buffer->tcp_length = htons((unsigned short)(tcp->doff * 4));  // tcp->doff : tcp head length = 5* 4=20		

	unsigned short checksum = tcp_udp_checksum(tcp_buffer, tcp_length/2,pseudo_buffer,sizeof(struct tcp_pseudo_header)/2);
	
	return checksum;
}

unsigned short tcp_checksum_1()
{
	unsigned char tcp_pseudo_header_array[12];

	int tcp_length =64 - 14 - 20;  // 총 보내는 패킷 길이 - (ethernet header + ip header)
	unsigned short *tcp_buffer = (unsigned short *)&sendbuff[34] ;

	//-----------------------------------------------------
	tcp_pseudo_header_array[0] = 192;  // source_ip
	tcp_pseudo_header_array[1] = 168;
	tcp_pseudo_header_array[2] = 0;
	tcp_pseudo_header_array[3] = 5;

	tcp_pseudo_header_array[4] = 192;  // destination_ip
	tcp_pseudo_header_array[5] = 168;
	tcp_pseudo_header_array[6] = 0;
	tcp_pseudo_header_array[7] = 3;

	tcp_pseudo_header_array[8] = 0; // reserved
	tcp_pseudo_header_array[9] = 6; // protocol : 6-TCP, 17-UDP
	tcp_pseudo_header_array[10] = (tcp_length & 0xff00)>> 8; // tcp_length
	tcp_pseudo_header_array[11] = tcp_length & 0xff; 
	//-----------------------------------------------------

	unsigned short checksum = tcp_udp_checksum(tcp_buffer, tcp_length/2,tcp_pseudo_header_array,sizeof(tcp_pseudo_header_array)/2);
	
	return checksum;
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
   
   for (int i=0; i<len_16; i++){
      sum += htons(*(buff)++);
   }
   do
   {
      sum = ((sum >> 16) + (sum & 0xffff));
   }
   while (sum & 0xffff0000);
   
   return (~sum);
}


void buff_init()
{
   
   // ---------------------------------------------------
   // Ethernet Packet
   // Destination MAC Address : FC-B3-BC-4B-EA-28
   sendbuff[0]  = 0xFC;
   sendbuff[1]  = 0xB3;
   sendbuff[2]  = 0xBC;
   sendbuff[3]  = 0x4B;
   sendbuff[4]  = 0xEA;
   sendbuff[5]  = 0x28;   
   // Source MAC Address : 00:0c:29:0f:c5:f3
   sendbuff[6]  = 0x06;
   sendbuff[7]  = 0x07;
   sendbuff[8]  = 0x08;
   sendbuff[9]  = 0x09;
   sendbuff[10]  = 0x01;
   sendbuff[11]  = 18;   // 100 : teacher's number -> don't touch
   // Type = ARP : 0x0806, IP : 0x0800
   sendbuff[12]  = 0x08;
   sendbuff[13]  = 0x00;
   
   // ---------------------------------------------------------
   // IP Packet
   sendbuff[14] = (4 << 4) | 5;   // Version, Header Length
   sendbuff[15] = 0;   // TOS
   sendbuff[16] = 0;   // Total Length
   sendbuff[17] = 64-14;   // Total Length   // ntohs(), htons()
   sendbuff[18] = 0;   // ID
   sendbuff[19] = 0;
   sendbuff[20] = 0;   // Flags, Fragment Offset
   sendbuff[21] = 0;
   sendbuff[22] = 64;   // TTL : Time to live
   sendbuff[23] = 6;   // Protocol Number
   sendbuff[24] = 0;   // Header Checksum
   sendbuff[25] = 0;
   
   // Source IP Address
   sendbuff[26] = 10;
   sendbuff[27] = 80;
   sendbuff[28] = 163;
   sendbuff[29] = 46;
   
   // Destination IP Address
   sendbuff[30] = 10;
   sendbuff[31] = 80;
   sendbuff[32] = 162;
   sendbuff[33] = 252;
   
      // Header checksum
   unsigned short header_checksum = checksum((unsigned short*)(&sendbuff[14]), 20/2);   // 20 bytes
   sendbuff[24] = (header_checksum & 0xff00) >> 8;
   sendbuff[25] = header_checksum & 0xff;
   
   // Data
   // TCP Header
   sendbuff[34] = (20003 & 0xff00) >> 8;   // Source Port
   sendbuff[35] = 20003 & 0xff;
   sendbuff[36] = (20000 & 0xff00) >> 8;   // Destination Port
   sendbuff[37] = 20000 & 0xff;
   
   // sequence number
   sendbuff[38] = 0; 
   sendbuff[39] = 0;
   sendbuff[40] = 0;
   sendbuff[41] = 100;
   
   // ack
   sendbuff[42] = 0; 
   sendbuff[43] = 0;
   sendbuff[44] = 0;
   sendbuff[45] = 0;
   
   sendbuff[46] = (4 << 4) | 5; // header length
   sendbuff[47] = 0b00000010;
   
   // window size
   sendbuff[48] = (64000 & 0xff00) >> 8;   // Source Port
   sendbuff[49] = 64000 & 0xff;
   
   // checksum
   sendbuff[50] = 0;
   sendbuff[51] = 0;
   
   // urgent pointer
   sendbuff[52] = 0;
   sendbuff[53] = 0;
   
   // User Data
   sendbuff[54] = 'h';
   sendbuff[55] = 'e';
   sendbuff[56] = 'h';
   sendbuff[57] = 'e';
   
	unsigned short checksum = tcp_checksum_1();
	sendbuff[50] =(checksum  & 0xff00) >> 8; 
	sendbuff[51] =(checksum & 0xff);
}



void send_data_process()
{

   unsigned int a = 0x12345678;
   unsigned char b = a;
   printf("%d\n", a);
   printf("%c\n", b);

   buff_init();
   

   printf("sending...\n");
   while(1)
   {
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


#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <errno.h>


#include<linux/if_packet.h>
#include<netinet/in.h>		 
#include<netinet/if_ether.h>    // for ethernet header
#include<netinet/ip.h>		// for ip header
#include<netinet/udp.h>		// for udp header
#include<netinet/tcp.h>
#include<arpa/inet.h>           // to avoid warning at inet_ntoa

#include<stdlib.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include <softPwm.h>

int serial;

char device[] = "/dev/ttyACM0";

unsigned long baudrate = 9600;

#define LED_PIN_1 1
#define LED_PIN_2 25

#define SERVO_PIN 0

struct sockaddr saddr;
struct sockaddr_in source,dest;

void recv_data_process(unsigned char* buffer,int buflen);

void led1On(void);
void led1Off(void);
void led2On(void);
void led2Off(void);
void servoLeft(void);
void servoRight(void);

int main()
{

	int sock_recv,saddr_len,buflen;

	unsigned char* buffer = (unsigned char *)malloc(65536); 
	memset(buffer,0,65536);
	
	printf("starting .... \n");

	sock_recv=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)); 
	if(sock_recv<0)
	{
		printf("error in socket\n");
		return -1;
	}
	
	if((serial = serialOpen(device, baudrate)) < 0) {
		fprintf(stdout, "응애 오류 났어 : %s\n", strerror (errno));
		exit(1);
	}
	
	if (wiringPiSetup() == -1) {
		fprintf(stdout, "응애 wiringPi :%s\n", strerror(errno));
		exit(1);
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

//==================================34==============================

void recv_data_process(unsigned char* buffer,int buflen)
{
//00:0c:29:36:ec:29
	if(((buffer[36] << 8)|buffer[37]) == 10018)
	{
		printf("IP Address : ");
		for(int i = 30; i < 33; i++) {
			printf("%d.", buffer[i]);
		}
		printf("%d", buffer[33]);
		printf("\n");
	
		printf("Port : ");
		printf("%d\n", (buffer[36] << 8)|buffer[37]);

		printf("Data : ");
		char str[6];
		for(int i = 42; i < 48; i++) {
			str[i-42] = buffer[i];
		}
		printf("%s", str); 
		printf("\n");	
		
		serialPuts(serial, str);
		/*
		if(strcmp(str,"led1on") == 0) {
			led1On();
		} else if(strcmp(str, "led1of") == 0) {
			led1Off();
		} else if(strcmp(str, "led2on") == 0) {
			led2On();
		} else if(strcmp(str, "led2of") == 0) {
			led2Off();
		} else if(strcmp(str, "serlef") == 0) {
			servoLeft();
		} else if(strcmp(str, "serrit") == 0) {
			servoRight();
		}
		*/
	}
}

void led1On() {
	pinMode(LED_PIN_1, OUTPUT);
	digitalWrite(LED_PIN_1, HIGH);
}

void led1Off() {
	pinMode(LED_PIN_1, OUTPUT);
	digitalWrite(LED_PIN_1, LOW);
}

void led2On() {
	pinMode(LED_PIN_2, OUTPUT);
	digitalWrite(LED_PIN_2, HIGH);
}

void led2Off() {
	pinMode(LED_PIN_2, OUTPUT);
	digitalWrite(LED_PIN_2, LOW);
}

void servoLeft() {
	softPwmCreate(SERVO_PIN, 0, 200);
	softPwmWrite(SERVO_PIN, 24);
}

void servoRight() {
	softPwmCreate(SERVO_PIN, 0, 200);
	softPwmWrite(SERVO_PIN, 5);
}





























#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int serial;

char device[] = "/dev/ttyACM0";

unsigned long baudrate = 9600;
unsigned long time = 0;

int main(void);
void loop(void);
void setup(void);

void modeOne(void);
void modeTwo(void);
void modeThree(void);
void modeFour(void);
void modeFive(void);
void modeSix(void);
void modeSeven(void);

void setup() {
	printf("Start!!!");
	fflush(stdout);
	
	if((serial = serialOpen(device, baudrate)) < 0) {
		fprintf(stdout, "응애 오류 났어 : %s\n", strerror (errno));
		exit(1);
	}
	
	if (wiringPiSetup() == -1) {
		fprintf(stdout, "응애 wiringPi :%s\n", strerror(errno));
		exit(1);
	}
	
}

void loop() {
	
	// 신호 읽기
	if(serialDataAvail(serial)) {
		char newChar = serialGetchar(serial);
		printf("%c", newChar);
		switch(newChar) {
			case '1':
				modeOne();
				break;
			case '2':
				modeTwo();
				break;
			case '3':
				modeThree();
				break;
			case '4':
				modeFour();
				break;
			case '5':
				modeFive();
				break;
			case '6':
				modeSix();
				break;
			case '7':
				modeSeven();
				break;
		}
				
		fflush(stdout);
	}
}

void modeOne() {
	printf("1 응애");
}

void modeTwo() {
	printf("2 응애");
}

void modeThree() {
	printf("3 응애");
}

void modeFour() {
	printf("4 응애");
}

void modeFive() {
	printf("5 응애");
}

void modeSix() {
	printf("6 응애");
}

void modeSeven() {
	printf("7 응애");
}

int main() {
	setup();
	while(1) loop();
	return 0;
}

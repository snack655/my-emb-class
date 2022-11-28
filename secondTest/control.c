#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <pthread.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include <softPwm.h>

int serial;

char device[] = "/dev/ttyACM0";

unsigned long baudrate = 9600;

#define LED_PIN 1
#define SERVO_PIN 0

int pwmFlag = 0;
int bright = 0;

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

void* Thread_LED_PWM(void* arg) {
	
	bright = 0;
	
	while(1) {
		for(int i = 0; i <= 1023; ++i) {
			bright++;
			delay(1);
		}
		
		for(int i = 1023; i >= 0; --i) {
			bright--;
			delay(1);
		}
	}
}

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
	
	pthread_t thread_led;
	pthread_create(&thread_led, NULL, Thread_LED_PWM, NULL);
	
}

void loop() {
	
	if(pwmFlag == 1) {
		pwmWrite(LED_PIN, bright);
	}
	
	// 신호 읽기
	if(serialDataAvail(serial)) {
		char newChar = serialGetchar(serial);
		printf("%c", newChar);
		switch(newChar) {
			case '1':
				pwmFlag=0;
				modeOne();
				break;
			case '2':
				pwmFlag=0;
				modeTwo();
				break;
			case '3':
				modeThree();
				break;
			case '4':
				pwmFlag=0;
				modeFour();
				break;
			case '5':
				pwmFlag=0;
				modeFive();
				break;
			case '6':
				pwmFlag=0;
				modeSix();
				break;
			case '7':
				pwmFlag=0;
				modeSeven();
				break;
		}
				
		fflush(stdout);
	}
}

void modeOne() {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
}

void modeTwo() {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
}

void modeThree() {
	pinMode(LED_PIN, PWM_OUTPUT);
	pwmFlag = 1;
}

void modeFour() {
	softPwmCreate(SERVO_PIN, 0, 200);

	softPwmWrite(SERVO_PIN, 24);
}

void modeFive() {
	softPwmCreate(SERVO_PIN, 0, 200);

	softPwmWrite(SERVO_PIN, 5);
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

#-*-coding:utf-8-*-

# 필요한 라이브러리를 불러옵니다.
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#센서에 연결한 Trig와 Echo 핀의 번호 설정
TRIG = 16
ECHO = 20

print("Distance measurement in progress")

BUZZ = 21

GPIO.setup(BUZZ, GPIO.OUT)
#Trig와 Echo 핀의 출력/입력 설정

GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

p = GPIO.PWM(BUZZ, 100)

#Trig핀의 신호를 0으로 출력
GPIO.output(TRIG, False)

print("Waiting for sensor to settle")
time.sleep(2)

Frq = [ 262, 294, 330, 349, 392, 440, 493, 523 ]

p.start(10)

try:
    while True:
        # Triger 핀에 펄스신호를 만들기 위해 1 출력
        GPIO.output(TRIG, True)
        time.sleep(0.00001) # 10μs 딜레이
        GPIO.output(TRIG, False)

		# start time
        while GPIO.input(ECHO)==0:
            start = time.time()
        while GPIO.input(ECHO)==1:
            stop= time.time() # Echo 핀 하강 시간

        check_time = stop - start
        distance = check_time * 34300 / 2
        
        if 1 <= distance and distance < 3:
            p.ChangeFrequency(Frq[0])
        elif 3 <= distance and distance < 5:
            p.ChangeFrequency(Frq[1])
        elif 5 <= distance and distance < 7:
            p.ChangeFrequency(Frq[2])
        elif 7 <= distance and distance < 9:
            p.ChangeFrequency(Frq[3])
        elif 9 <= distance and distance < 11:
            p.ChangeFrequency(Frq[4])
        elif 11 <= distance and distance < 13:
            p.ChangeFrequency(Frq[5])
        elif 13 <= distance and distance < 15:
            p.ChangeFrequency(Frq[6])
        elif 15 <= distance and distance < 17:
            p.ChangeFrequency(Frq[7])
        else:
            p.ChangeFrequency(1)

        print("Distance : %.1f cm" % distance)
        time.sleep(0.4) # 0.4초 간격으로 센서 측정

except KeyboardInterrrupt:
	print("Measurement stopped by User")
	GPIO.cleanup()
p.stop()
GPIO.cleanup()

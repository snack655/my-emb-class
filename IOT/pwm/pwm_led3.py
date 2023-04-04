import RPi.GPIO as GPIO
import time

button_pin = 21
led_pin = 18


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.setup(led_pin, GPIO.OUT)
p = GPIO.PWM(led_pin, 100)

pwm_on = False

p.start(0)

cnt = 0 # 0 1(30) 2(60) 3(100)

def button_callback(channel):
	global cnt
	cnt += 1
	
	if cnt > 3:
		cnt = 0
			
	if cnt == 0:
		for dc in range(100, -1, -1):
			p.ChangeDutyCycle(dc)
			time.sleep(0.01)
	elif cnt == 1:
		for dc in range(0, 30, 1):
			p.ChangeDutyCycle(dc)
			time.sleep(0.01)
	elif cnt == 2:
		for dc in range(30, 60, 1):
			p.ChangeDutyCycle(dc)
			time.sleep(0.01)
	elif cnt == 3:
		for dc in range(60, 101, 1):
			p.ChangeDutyCycle(dc)
			time.sleep(0.01)
	
GPIO.add_event_detect(button_pin, GPIO.RISING, callback=button_callback, bouncetime=300)

while 1:
	time.sleep(0.1)

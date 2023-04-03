import RPi.GPIO as GPIO
import time

worker_green = 21
worker_red = 20

car_green = 4
car_yellow = 16
car_red = 12

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)

GPIO.setup(car_green, GPIO.OUT)
GPIO.setup(car_yellow, GPIO.OUT)
GPIO.setup(car_red, GPIO.OUT)

GPIO.setup(worker_green, GPIO.OUT)
GPIO.setup(worker_red, GPIO.OUT)

while True:
	GPIO.output(car_green, 1)
	GPIO.output(worker_red, 1)
	
	GPIO.output(car_yellow, 0)
	GPIO.output(car_red, 0)
	GPIO.output(worker_green, 0)
	
	time.sleep(3)
	
	GPIO.output(car_yellow, 1)
	
	GPIO.output(worker_red, 0)
	GPIO.output(car_green, 0)
	GPIO.output(car_red, 0)
	GPIO.output(worker_green, 0)
	
	time.sleep(3)
	
	GPIO.output(car_red, 1)
	GPIO.output(worker_green, 1)
		
	GPIO.output(worker_red, 0)
	GPIO.output(car_green, 0)
	GPIO.output(car_yellow, 0)
	
	time.sleep(3)
	
GPIO.cleanup()

import RPi.GPIO as GPIO
import time

button_pin = 21

red_pin = 20
blue_pin = 16

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)

GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.setup(red_pin, GPIO.OUT)
GPIO.setup(blue_pin, GPIO.OUT)


while 1:
	while(GPIO.input(button_pin) == GPIO.HIGH):
		GPIO.output(blue_pin, 1)
		GPIO.output(red_pin, 0)
		time.sleep(0.1)
		GPIO.output(blue_pin, 0)
		GPIO.output(red_pin, 1)

		time.sleep(0.1)

	GPIO.output(red_pin, 0)
	GPIO.output(blue_pin, 0)
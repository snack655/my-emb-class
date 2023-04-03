import RPi.GPIO as GPIO
import time

led_pin_1 = 16
led_pin_2 = 20
led_pin_3 = 21

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)

GPIO.setup(led_pin_1, GPIO.OUT)
GPIO.setup(led_pin_2, GPIO.OUT)
GPIO.setup(led_pin_3, GPIO.OUT)

while True:
	GPIO.output(led_pin_1, 1)
	GPIO.output(led_pin_2, 1)
	GPIO.output(led_pin_3, 1)
	time.sleep(0.1)
	GPIO.output(led_pin_1, 0)
	GPIO.output(led_pin_2, 0)
	GPIO.output(led_pin_3, 0)
	time.sleep(0.1)
GPIO.cleanup()
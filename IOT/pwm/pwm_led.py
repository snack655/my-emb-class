import RPi.GPIO as GPIO
import time

button_pin = 21
led_pin = 18

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.setup(led_pin, GPIO.OUT)
p = GPIO.PWM(led_pin, 100)

p.start(0)

pwm_on = False

try:
	while True:
		if GPIO.input(button_pin) == GPIO.LOW:
			if not pwm_on:
				pwm_on = True
				while pwm_on:
					for dc in range(0, 101, 1):
						p.ChangeDutyCycle(dc)
						time.sleep(0.01)
					for dc in range(100, -1, -1):
						p.ChangeDutyCycle(dc)
						time.sleep(0.01)
		else:
			if pwm_on:
				p.stop()
				pwm_on = False
		time.sleep(0.01)
	
except KeyboardInterrupt:
	pass
	
p.stop()
GPIO.cleanup()

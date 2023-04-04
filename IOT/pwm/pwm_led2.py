import RPi.GPIO as GPIO
import time
import threading

button_pin = 21
led_pin = 18
already_start = False


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.setup(led_pin, GPIO.OUT)
p = GPIO.PWM(led_pin, 100)

pwm_on = False

p.start(0)


def pwm_led_on():
	while True:
		for dc in range(0, 101, 1):
			p.ChangeDutyCycle(dc)
			time.sleep(0.01)
		for dc in range(100, -1, -1):
			p.ChangeDutyCycle(dc)
			time.sleep(0.01)
				
t = threading.Thread(target=pwm_led_on)

def button_callback(channel):
	global pwm_on
	global already_start
	if pwm_on == False:
		if not already_start:
			t.start()
			already_start = True
		else:
			p.start(0)
	else:
		p.stop()
		
	pwm_on = not pwm_on

GPIO.add_event_detect(button_pin, GPIO.RISING, callback=button_callback, bouncetime=300)

while 1:
	time.sleep(0.1)

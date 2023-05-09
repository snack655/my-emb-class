import RPi.GPIO as GPIO
import time
import picamera
import datetime

pirPin = 16

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(pirPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

camera = picamera.PiCamera()
camera.resolution = (1024, 768)

try:
    while True:
        sensorValue = GPIO.input(pirPin)
        print(sensorValue)
        if sensorValue == 1:
            now = str(datetime.datetime.now())
            idx = now.find('.')
            nnow = now[:idx]
            camera.capture(nnow + ".jpg")
        time.sleep(0.5)

except KeyboardInterrupt:
    pass

GPIO.cleanup()

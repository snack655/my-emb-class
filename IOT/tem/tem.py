import time
import Adafruit_DHT
import RPi.GPIO as GPIO

sensor = Adafruit_DHT.DHT11
pin = 4

green = 16
blue = 20
red = 21

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)
GPIO.setup(red, GPIO.OUT)


try:
    while True:
        h, t = Adafruit_DHT.read_retry(sensor, pin)
        v = (1.8 * t) - (0.55 * (1 - (h / 100.0)) * (1.8 * t - 26)) + 32
        if 76 <= v:
            GPIO.output(red, 1)
            GPIO.output(green, 0)
            GPIO.output(blue, 0)
        elif 70 <= v:
            GPIO.output(red, 0)
            GPIO.output(green, 1)
            GPIO.output(blue, 0)
        else:
            GPIO.output(red, 0)
            GPIO.output(green, 0)
            GPIO.output(blue, 1)

        if (h is not None) and (t is not None):
            print("Temperatur = {0:0.1f}*C Humidity = {1:0.1f}%".format(t, h))
        else:
            print('Read error')
        time.sleep(1)
except KeyboardInterrupt:
    print("Terminated by Keyboard")

finally:
    print("End of Program")

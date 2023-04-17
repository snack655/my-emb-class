import spidev
import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.OUT)
p = GPIO.PWM(18, 523)

delay = 0.5
pot_channel = 0

spi = spidev.SpiDev()

spi.open(0, 0)

spi.max_speed_hz = 100000

def readadc(adcnum):
    if adcnum > 7 or adcnum < 0:
        return -1
    r = spi.xfer2([1, 8 + adcnum << 4, 0])
    data = ((r[1] & 3) << 8) + r[2]
    return data

while True:
    pot_value = readadc(pot_channel)
    print("------------------------------")
    print("POT VALUE %d" % pot_value)
    if pot_value > 242:
        p.start(10)
    else:
        p.stop()
    time.sleep(delay)

GPIO.cleanup()

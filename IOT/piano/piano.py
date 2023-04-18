import RPi.GPIO as GPIO
import time

button_do = 14
button_re = 15
button_mi = 18
button_pa = 23
button_sol = 24

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(button_do, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button_re, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button_mi, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button_pa, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(button_sol, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.setup(21, GPIO.OUT)

p = GPIO.PWM(21, 100)

Frq = [ 65, 147, 330, 698, 1568 ]
speed = 0.5
idx = 0

letsgo = False

def do(channel):
    global idx
    global letsgo
    idx = 0
    letsgo = True
    time.sleep(1)
    letsgo = False

def re(channel):
    global idx
    global letsgo
    idx = 1
    letsgo = True
    time.sleep(1)
    letsgo = False


def mi(channel):
    global idx
    global letsgo
    idx = 2
    letsgo = True
    time.sleep(1)
    letsgo = False


def pa(channel):
    global idx
    global letsgo
    idx = 3
    letsgo = True
    time.sleep(1)
    letsgo = False

def sol(channel):
    global idx
    global letsgo
    idx = 4
    letsgo = True
    time.sleep(1)
    letsgo = False

GPIO.add_event_detect(button_do, GPIO.RISING, callback=do, bouncetime=300)
GPIO.add_event_detect(button_re, GPIO.RISING, callback=re, bouncetime=300)
GPIO.add_event_detect(button_mi, GPIO.RISING, callback=mi, bouncetime=300)
GPIO.add_event_detect(button_pa, GPIO.RISING, callback=pa, bouncetime=300)
GPIO.add_event_detect(button_sol, GPIO.RISING, callback=sol, bouncetime=300)

p.start(10)

try:
    while 1:
        if letsgo:
            p.ChangeFrequency(Frq[idx])
        else:
            p.ChangeFrequency(1)
except KeyboardInterrupt:
    pass
p.stop()
GPIO.cleanup()

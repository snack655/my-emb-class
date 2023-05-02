import serial
import time
import RPi.GPIO as GPIO

bleSerial = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1.0)

green = 16
blue = 20
red = 21

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)
GPIO.setup(red, GPIO.OUT)

try:
    sendData = "Is MOOOOONGS rp \r\n"
    bleSerial.write(sendData.encode())
    while True:
        line = bleSerial.readline().decode('utf-8').rstrip()
        if len(line) != 0:
            print(line)
            if line == "green on":
                GPIO.output(green, 1)
            elif line == "green off":
                GPIO.output(green, 0)
            elif line == "blue on":
                GPIO.output(blue, 1)
            elif line == "blue off":
                GPIO.output(blue, 0)
            elif line == "red on":
                GPIO.output(red, 1)
            elif line == "red off":
                GPIO.output(red, 0)

except KeyboardInterrupt:
    pass

bleSerial.close()

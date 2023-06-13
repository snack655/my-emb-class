import requests
import re
import RPi.GPIO as GPIO

green = 16
blue = 20
red = 21

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)
GPIO.setup(red, GPIO.OUT)

GPIO.output(green, 0)
GPIO.output(red, 0)
GPIO.output(blue, 0)

url = "https://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getCtprvnRltmMesureDnsty?serviceKey=7sjLpnu9tSVVDEO9L5VhYSOUKCJanT%2BhUIMrkKxGT9E5uYLiS3xsasvk4WJKttofCuWYq%2BHQjkqJgzreyugVew%3D%3D&returnType=xml&numOfRows=100&pageNo=1&sidoName=대구&ver=1.0"
response = requests.get(url)

pm25 = re.findall(r'<pm25Value>(.+)</pm25Value>', response.text)
stationName = re.findall(r'<stationName>(.+)</stationName>', response.text)

hpm = int(pm25[stationName.index("화원읍")])
print(hpm)


if hpm <= 30:
	GPIO.output(green, 1)
	GPIO.output(red, 0)
	GPIO.output(blue, 0)
elif hpm < 80:
	GPIO.output(green, 0)
	GPIO.output(red, 0)
	GPIO.output(blue, 1)
elif hpm < 150:
	GPIO.output(green, 0)
	GPIO.output(red, 1)
	GPIO.output(blue, 0)
else:
	GPIO.output(green, 1)
	GPIO.output(red, 1)
	GPIO.output(blue, 1)

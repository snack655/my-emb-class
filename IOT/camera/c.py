import picamera
import time
import datetime


camera = picamera.PiCamera()
camera.resolution = (1024, 768)

now = str(datetime.datetime.now())
idx = now.find('.')
nnow = now[:idx]
print(nnow)

camera.capture(nnow + ".jpg")

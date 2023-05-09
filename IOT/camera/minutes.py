import datetime
import picamera

camera = picamera.PiCamera()
camera.resolution = (1024, 768)

while True:
    now = datetime.datetime.now()
    next_capture = (now + datetime.timedelta(minutes=1)).replace(second=0, microsecond=0)

    while datetime.datetime.now() < next_capture:
        pass
    now = str(datetime.datetime.now())
    idx = now.find('.')
    nnow = now[:idx]
    camera.capture(nnow + '.jpg')

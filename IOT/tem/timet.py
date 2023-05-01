import time
import datetime
import Adafruit_DHT

sensor = Adafruit_DHT.DHT11
pin = 4

try:
    while True:
        h, t = Adafruit_DHT.read_retry(sensor, pin)
        if (h is not None) and (t is not None):
            now = datetime.datetime.now()
            f = open('temphumi.txt', 'a')
            f.write(str(now)+" - TEMP : {0:0.1f}*C | HUMID = {1:0.1f}%".format(t, h) + '\r\n')
            f.close()
        time.sleep(1.0)

except KeyboardInterrupt:
    pass

from flask import Flask, render_template, request
import RPi.GPIO as GPIO

app = Flask(__name__)

ledPin = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(ledPin, GPIO.OUT)
GPIO.output(ledPin, 0)

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/data', methods=["POST"])
def handle_data():
    led = request.form.get("led")
    if led == "on":
        GPIO.output(ledPin, 1)
        return render_template("index.html")
    elif led == "off":
        GPIO.output(ledPin, 0)
        return render_template("index.html")

@app.route('/ledon')
def ledOn():
    GPIO.output(ledPin, 1)
    return "<h1> LED ON </h1>"

@app.route('/ledoff')
def ledOff():
    GPIO.output(ledPin, 0)
    return "<h1> LED OFF </h1>"

if __name__ == "__main__":
    app.run(host = "0.0.0.0", port = "80")

#define LED_PIN 13
#define LED_PIN2 6
#define SERVO_PIN 5

void setup() {
  Serial.setTimeout(100);
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
}

int cycle = 1000;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    String str = Serial.readStringUntil('\n');
    Serial.println(str);

    if(str == "LED ON 1") {
      digitalWrite(LED_PIN, HIGH);
    } else if (str == "LED OFF 1") {
      digitalWrite(LED_PIN, LOW);
    } else if (str == "LEFT") {
      servo(SERVO_PIN, 2400);
    } else if (str == "RIGHT") {
       servo(SERVO_PIN, 500);
    } else if(str == "LED ON 2") {
      digitalWrite(LED_PIN2, HIGH);
    } else if(str == "LED OFF 2") {
      digitalWrite(LED_PIN2, LOW);
    }
  }
}

int interval = 20000;

void servo(int pin, int cycle) { // pulse width: 500 ~ 2400 ... sg90
  for (int i = 0; i < 100; i++) {
    digitalWrite(pin,HIGH);
    delayMicroseconds(cycle);
    digitalWrite(pin,LOW);
    delayMicroseconds(interval - cycle);
  }
}

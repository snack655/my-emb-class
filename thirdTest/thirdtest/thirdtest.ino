#define LED_PIN 13
#define LED_PIN2 6
#define SERVO_PIN 5

int cycle = 1000;

void setup() {
  Serial.setTimeout(100);
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
}

void loop() {

  if (Serial.available() > 0) {
    String str = Serial.readStringUntil('\n');
    Serial.println(str);

    if(str == "led1on") {
      digitalWrite(LED_PIN, HIGH);
    } else if(str == "led1of") {
      digitalWrite(LED_PIN, LOW);
    } else if(str == "led2on") {
      digitalWrite(LED_PIN2, HIGH);
    } else if(str == "led2of") {
      digitalWrite(LED_PIN2, LOW);
    } else if(str == "serlef") {
      servo(SERVO_PIN, 2400);
    } else if(str == "serrit") {
      servo(SERVO_PIN, 500);
    }
  }

}

int interval = 20000;

void servo(int pin, int cycle) {
  for (int i = 0; i < 100; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(cycle);
    digitalWrite(pin, LOW);
    delayMicroseconds(interval - cycle);
  }
}

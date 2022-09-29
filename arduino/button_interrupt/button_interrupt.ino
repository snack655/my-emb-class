void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);

  attachInterrupt(1, myISR, CHANGE);
}

void loop() {
  

}

unsigned long first_time = 0;
unsigned long second_time = 0;
int diff_time = 0;

void myISR() {
  int in_value = digitalRead(3);
  if (in_value == 1) {
    first_time = micros();
    //Serial.println("Rising");
  } else {
    second_time = millis();
    //Serial.println("Falling");
    diff_time = second_time - first_time;
    Serial.println(diff_time);
  }
}
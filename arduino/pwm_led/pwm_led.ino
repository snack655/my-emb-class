void setup() {

  Serial.begin(9600);

  Serial.println("haha");

  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
}

int count = 0;
int count2 = 0;
int count_100ms = 0;
int count_200ms = 0;
int duty = 1;
int duty2 = 1;

void loop() {

  // for(int i = 0; i < 100; i++){
  //   digitalWrite(13, HIGH);
  //   delay(9);
  //   digitalWrite(13, LOW);
  //   delay(1);
  // }

  // for (int i = 0;i < 100; i++) {
  //   digitalWrite(13, HIGH);
  //   delay(1);
  //   digitalWrite(13, LOW);
  //   delay(13);
  // }

  // 100 -----------------------------------
  if (count == 100) {
    count = 0;
    digitalWrite(13, HIGH);

  } else if (count == duty) {
    digitalWrite(13, LOW);
  }

  // 200 -----------------------------------
  if (count2 == 200) {
    count2= 0;
    digitalWrite(9, HIGH);
  } else if (count2 == duty2) {
    digitalWrite(9, LOW);
  }

  //100 ----------------------------------------

  if (count_100ms == 100) {
    count_100ms = 0;
    duty++;
    duty2++;
    if(duty == 99) duty = 1;
    if(duty2 == 199) duty2 = 1;
  }

  count++;
  count2++;
  count_100ms++;
  //delay(1);
  delayMicroseconds(100);

}
void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);

}

char btn_flag = 0;
char btn_flag_down = 0;
char btn_flag_up = 0;

void loop() {
  
  int in_value = digitalRead(3);

  // if (in_value == 1) {

  //   if(btn_flag == 0) {
  //     btn_flag = 1;
  //     Serial.println("Down");
  //   }
    
  // } else {
  //   if (btn_flag == 1) {
  //     btn_flag = 0;
  //     Serial.println("Up");
  //   }
  // }

  // ----------------------------------------------------------

  if (in_value == 1 && btn_flag == 0) {

    btn_flag = 1;
    Serial.println("Down");
    
  } else if (in_value == 0 && btn_flag == 1) {
      btn_flag = 0;
      //Serial.println("Up");
  }

  delay(10);
  

}

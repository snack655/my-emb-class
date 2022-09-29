void setup() {
  Serial.begin(9600);
}

char x_flag_left = 0;
char x_flag_right = 0;

// void loop() {
//   int x_value = analogRead(A4);

//   if (x_value < 400) {

//     if(x_flag_left == 0) {
//       x_flag_left = 1;
//       Serial.println("left");
//     }

//   } else if(x_value > 600) {

//     if(x_flag_right == 0) {

//       x_flag_right = 1;
//       Serial.println("right");
//     }

//   } else {
//       x_flag_right= 0;
//       x_flag_left = 0;
//   }

//   delay(10);

// }


int analog_port[2] = { A4, A5 };
char flag_left[2] = { 0, 0 };
char flag_right[2] = { 0, 0 };


void loop() {
  for(int i = 0; i < 2; i++) {
    int value = analogRead(analog_port[i]);

    if (value < 400 && flag_left[i] == 0) {

      flag_left[i] = 1;
      if(i == 0) Serial.println("left");
      else if(i == 1) Serial.println("up");

    } else if(value > 600 && flag_right[i] == 0) {

      flag_right[i] = 1;
      if(i==0) Serial.println("right");
      else if(i == 1) Serial.println("down");

    } else if(value > 400 && value < 600) {
        flag_left[i] = 0;
        flag_right[i] = 0;
    }
    delay(5);
  }


}

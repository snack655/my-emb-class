void setup() {


  Serial.begin(9600);

  attachInterrupt(1, remoconISR, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int index = 0;
unsigned long recv_time[40];
unsigned int diff_time[33];
int bit_value[32];

void remoconISR() {
  //Serial.println("haha");

  recv_time[index] = micros();
  index++;
  if(index == 34) {
    index = 0;

    // for (int i = 0; i < 34; i++) {
    //   Serial.println(recv_time[i]);
    // }

    for (int i = 0; i < 33; i++) {
      diff_time[i] = recv_time[i + 1] - recv_time[i];
    }

    // for(int i = 0; i < 33; i++) {
    //   Serial.println(diff_time[i]);
    // }

    for (int i = 0; i < 32; i++) {
      if(diff_time[i + 1] > 1000 && diff_time[i+1] < 1500) {
        bit_value[i] = 0;
      } else if(diff_time[i + 1] > 2000 && diff_time[i + 1] < 2500) {
        bit_value[i] = 1;
      }
    }

    // for(int i = 0; i < 33; i++) {
    //   Serial.println(bit_value[i]);
    // }

    for (int i = 16; i < 24; i++) {
      Serial.println(bit_value[i]);
    }

  } 
}

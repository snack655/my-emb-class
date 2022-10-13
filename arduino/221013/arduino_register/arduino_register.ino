void setup() {
  Serial.begin(9600);

  //pinMode(13, OUTPUT);
  DDRB |= (0x01 << 5);

  // PD3 : INPUT mode (Button)
  DDRD &= ~(0x01 << 3);
}

void loop() {

  
  // delay(10);
  
  // unsigned char in_value = PIND;
  // if (in_value & (0x01 << 3)) {
  //   PORTB |= (0x01 << 5);
  // } else {
  //   PORTB &= ~(0x01 << 5);
  // }
  // delay(10);

  // //digitalWrite(13, HIGH);
  // PORTB |= (0x01 << 5);
  // delay(1000);

  // //digitalWrite(13, LOW);
  // PORTB &= ~(0x01 << 5);
  // delay(1000);

  int invalue = digitalRead(3);
  if(invalue == 1) {
    PORTB |= (0x01 << 5);
  } else {
    PORTB &= ~(0x01 << 5);
  }

}

int digital_read(int pin_num) {

  int pin_value = 0;
  unsigned char in_value = 0;

  if (pin_num <= 7) {
    DDRD &= ~(0x01 << pin_num);
    
    in_value = PIND;
    if (in_value & (0x01 << pin_num)) {
      pin_value = 1;
    } else {
      pin_value = 0;
    }

  } else if(pin_num >= 8 && pin_num <= 13) {
    
    DDRD &= ~(0x01 << (pin_num - 8));
    
    in_value = PINB;
    if (in_value & (0x01 << pin_num)) {
      pin_value = 1;
    } else {
      pin_value = 0;
    }
  }

  return pin_value;
}

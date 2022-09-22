#define SCL 19
#define SDA 18

#define SCL_HIGH() digitalWrite(SCL, HIGH)
#define SCL_LOW() digitalWrite(SCL, LOW)
#define SDA_HIGH() digitalWrite(SDA, HIGH)
#define SDA_LOW() digitalWrite(SDA, LOW)

void setup() {
  Serial.begin(9600);

  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
}

void loop() {
  PCF8574_set(0xff);
  delay(1000);
  PCF8574_set(0x00);
  delay(1000);
}

// start condition
void i2c_start() {
  SCL_HIGH();
  SDA_HIGH();
  SDA_LOW();
}

// Device Address
void i2c_8bit_set(unsigned char data) {
  for (int i = 0; i < 8; i++) {
    if (data & 0x80 >> i) {
      SDA_HIGH();
    } else {
      SDA_LOW();
    }
    SCL_HIGH();
    SCL_LOW();
  }
}

void i2c_ack() {
  pinMode(SDA, INPUT);
  SCL_HIGH();
  int ack_value = digitalRead(SDA);
  Serial.println(ack_value);
  pinMode(SDA, OUTPUT);
  SCL_LOW();
}

void i2c_stop() {
  SDA_LOW();
  SCL_HIGH();
  SDA_HIGH();
}

void PCF8574_set(unsigned char data) {

  // Start
  i2c_start();
  i2c_8bit_set(0x27 << 1);
  // ACK Device for Address
  i2c_ack();
  // Data
  i2c_8bit_set(data);
  // ACK Device for Address
  i2c_ack();
  // Stop
  i2c_stop();

}
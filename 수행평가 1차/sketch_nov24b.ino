#define LED1_PIN 13
#define LED2_PIN 6

void setup()
{
  Serial.setTimeout(100);
  Serial.begin(9600);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop()
{
  if (Serial.available())
  {
    String str = Serial.readString();
    if (str == "1on")
    {
      digitalWrite(LED1_PIN, HIGH);
      //Serial.println("LED1_on");
    }
    else if (str == "1of")
    {
      digitalWrite(LED1_PIN, LOW);
      //Serial.println("LED1_off");
    }
    if (str == "2on")
    {
      digitalWrite(LED2_PIN, HIGH);
      //Serial.println("LED2_on");
    }
    else if (str == "2of")
    {      digitalWrite(LED2_PIN, LOW);
      //Serial.println("LED2_off");
    }
  }
}

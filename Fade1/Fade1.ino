int led = 9;  //pin that the LED is attached to
int brightness = 0; //Brightness of LED
int fadeAmount = 10; //points to fade the LED by



void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led, brightness);

  brightness = brightness + fadeAmount;

  if(brightness == 0 || brightness == 1023) {
    fadeAmount = -fadeAmount;
  }

  delay(30);

}

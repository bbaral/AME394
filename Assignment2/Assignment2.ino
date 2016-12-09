//Bikram Baral
//Assignment 2

const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 4;
const int pin4 = 5;
const int pin5 = 6;
const int pin6 = 7;
const int pin7 = 8;
const int pin8 = 9;
const int pin9 = 10;
const int pin10 = 11;
//pin for the temperature sensor
int sensorPin = 13;

void setup() {

  Serial.begin(9600);
  // make the pins outputs:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {

  int reading = analogRead(sensorPin);

  float voltage = reading * 5.0;
  voltage /= 1024.0;
  //getting *C temperature
  float TempC = (voltage - 0.49) * (100);
  //converting *C to *F
  float TempF = (TempC * 9.0 / 5.0) + 32.0;

  int percent = Serial.parseInt();


  int TemporaryValue = TempF;
  percent = TemporaryValue;
  Serial.println("Current Temperature " + percent);


  while (Serial.available() > 0) {
    if (Serial.read() == '\n')
    {
      if (percent > 40) {
        digitalWrite(pin1, HIGH);
      } else {
        digitalWrite(pin1, LOW);
      }
      if (percent > 50) {
        digitalWrite(pin2, HIGH);
      } else {
        digitalWrite(pin2, LOW);
      }
      if (percent > 60) {
        digitalWrite(pin3, HIGH);
      } else {
        digitalWrite(pin3, LOW);
      }
      if (percent > 70) {
        digitalWrite(pin4, HIGH);
      } else {
        digitalWrite(pin4, LOW);
      }
      if (percent > 80) {
        digitalWrite(pin5, HIGH);
      } else {
        digitalWrite(pin5, LOW);
      }
      if (percent > 90) {
        digitalWrite(pin6, HIGH);
      } else {
        digitalWrite(pin6, LOW);
      }
      if (percent > 100) {
        digitalWrite(pin7, HIGH);
      } else {
        digitalWrite(pin7, LOW);
      }
      if (percent > 110) {
        digitalWrite(pin8, HIGH);
      } else {
        digitalWrite(pin8, LOW);
      }

      if (percent > 125) {
        digitalWrite(pin9, HIGH);
      } else {
        digitalWrite(pin9, LOW);
      }

      if (percent > 140) {
        digitalWrite(pin10, HIGH);
      } else {
        digitalWrite(pin10, LOW);
      }


      delay(1000);
    }
  }
}

/*
 * Name: Bikram Baral
 * Assignment: 2 - Temperature Sensor
 */

int ledPinpoint = D3;
 int tmp36sensor_pin = 5;
 
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int pin_value;
  int fah;
  

  int reading = analogRead(tmp36sensor_pin);
  float voltage = reading * .004882814;
  voltage /= 1024.0;
  analogWrite(ledPinpoint, voltage);
  float temperatureC = (voltage - 0.5) * 80;
  float fah = temperatureC * 1.8 + 32;
  Serial.print("Current temperature is ");
  Serial.print(temperatureC);
  Serial.print(" C");
  //putting the condition for LED
  if(fah > 70 && fah < 150) 
  {
    digitalWrite(fah, HIGH)
  }
  Serial.print("Current temperature is ");
  Serial.print(fah);
  Serial.print(" F");
  delay(400);
}

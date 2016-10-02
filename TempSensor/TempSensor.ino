/*
 * Name: Bikram Baral
 * Assignment: 2 - Temperature Sensor
 */



/*  Show temperature with  TMP36/LM35/2N3904 temperature sensor
  copy right John Yu
  connect VS1838B to  D10 see http://osoyoo.com/?p=160
*/
 int tmp36sensor_pin = 5;
//int analog_no = 5 ;// define A5 as input signal pin
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int pin_value;
  //int temperature;
  int fah;
  
  //pin_value = analogRead(analog_no);
  
  //temperature = (44*pin_value)>>8 ;
  int reading = analogRead(tmp36sensor_pin);
  float voltage = reading * .004882814;
  //voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 80;
  Serial.print("Current temperature is ");
  Serial.print(temperatureC);
  Serial.println("C");
  fah = temperatureC * 1.8 + 32;
  Serial.print("Current temperature is ");
  Serial.print(fah);
  Serial.println("F");
  delay(400);
}

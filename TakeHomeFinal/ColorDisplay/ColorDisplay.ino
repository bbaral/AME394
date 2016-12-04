#include <b64.h>
#include <HttpClient.h>

/* RGB module project code
 * tutorial url: http://osoyoo.com/?p=549
 */

int redpin = 11; //select the pin for the red LED
int bluepin = 10; // select the pin for the  blue LED
int greenpin = 9; // select the pin for the green LED

const char* host = "ec2-54-244-202-56.us-west-2.compute.amazonaws.com";


int val;

int potentiometer = 0; //Potentiometer to A0

int position;

void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //This is for potentiometer
  position = map(analogRead(potentiometer), 0, 1023, 0, 255);

  HttpClient client;
    const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/addFinalData";

  url += "?Value=";

  url += position;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  for (val = 255; val > 0; val--)
  {
    analogWrite(11, val);
    analogWrite(10, val - position);
    analogWrite(9, val - position);
    delay(1);
  }
  for (val = 0; val < 255; val++)
  {
    analogWrite(11, val);
    analogWrite(10, val - position);
    analogWrite(9, val - position);
    delay(1);
  }
  Serial.println(url, DEC);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}

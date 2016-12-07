/* RGB module project code
   tutorial url: http://osoyoo.com/?p=549
*/
#include <ESP8266WiFi.h>

const char* ssid     = "Bikram's iPhone";
const char* password = "f7krau06qg7l";

const char* host = "ec2-54-244-202-56.us-west-2.compute.amazonaws.com";
//const char* host = "54.244.202.56";
//int redpin = 11; //select the pin for the red LED
//int bluepin = 10; // select the pin for the  blue LED
//int greenpin = 9; // select the pin for the green LED

const int redpin = 3;
const int bluepin = 2;
const int greenpin = 1;

int val;

int potentiometer = A0; //Potentiometer to A0

int position;

void setup() {

  Serial.begin(115200);
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop()
{
  delay(5000);
  ++value;
  //This is for potentiometer
  position = map(analogRead(potentiometer), 0, 1023, 0, 255);

  for (val = 255; val > 0; val--)
  {
    analogWrite(redpin, val);
    analogWrite(bluepin, val - position);
    analogWrite(greenpin, val - position);
    //delay(100);
  }
  for (val = 0; val < 255; val++)
  {
    analogWrite(redpin, val);
    analogWrite(bluepin, val - position);
    analogWrite(greenpin, val - position);
    //delay(100);
  }

  WiFiClient client;
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

  // This will send the request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
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

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
 // Serial.println(url, DEC);
  Serial.println();
  Serial.println("Closing connection");
}


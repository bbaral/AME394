/* RGB module project code
   tutorial url: http://osoyoo.com/?p=549
*/
#include <ESP8266WiFi.h>

const char* ssid     = "<enter hotspot username>";
const char* password = "<enter hotspot password>";

const char* host = "<enter hostname>";

const int LedPin = D1;
const int SensorPin = D2;
int inputVal;

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(LedPin, OUTPUT);
  pinMode (SensorPin, INPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  inputVal = digitalRead(SensorPin);
  if (inputVal == HIGH)
  {
    digitalWrite(LedPin, HIGH); //if no magnetic field is detected, D9 LED is off
  }
  else
  {
    digitalWrite(LedPin, LOW); //if magnetic field is detected, D9 LED turns on
  }
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/addFinalData";

  url += "?value=";

  url += inputVal;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
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
  
  Serial.println();
  Serial.println("Closing connection");
}


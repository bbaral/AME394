 /*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "<enter hotspot username>";
const char* password = "<enter hotspot password>";

const char* host = "<enter hostname>";

const int led = D1;
int brightness = 0;
int fadeAmount = 3;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);

  // We start by connecting to a WiFi network

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

void loop() {
  delay(1000);
  ++value;


  brightness = brightness + fadeAmount;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  } 
  
  // We now create a URI for the request
  String url = "/getReading";
  
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
  
  while(client.available()){
if(client.find("\r\n\r\n")) {
  String line = client.readStringUntil('\r');
  int brightness8b = line.toInt();
  brightness = map(brightness8b, 0, 255, 0, 1023);
  Serial.println(brightness);
  analogWrite(led, brightness);
}
  }
  
  Serial.println();
  Serial.println("closing connection");
}


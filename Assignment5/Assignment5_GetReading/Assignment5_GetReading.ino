 /*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "Bikram's iPhone";
const char* password = "f7kr*****7l";

const char* host = "ec2-54-244-202-56.us-west-2.compute.amazonaws.com";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

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

 // brightness = map(analogRead(pot), 0, 1023, 0, 255);

  //analogWrite(led, brightness);

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
  /*
  url += streamId;
  url += "?private_key=";
  url += privateKey;
  url += "&value=";
  url += value;
  */
  
  Serial.print("Requesting URL: ");
  Serial.println(url);

//  if(brightness == 0 || brightness == 255) {
//    fadeAmount = -fadeAmount;
//  }
  
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
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
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


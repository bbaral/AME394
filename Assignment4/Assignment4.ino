
/*  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

  #include <Wire.h> 
  
  #include <math.h> 
  
  int BH1750address = 0x23; 
  
  byte buff[2];

#define dht_dpin A0
byte bGlobalErr;
byte dht_dat[5]; 


#include <ESP8266WiFi.h>

const char* ssid     = "Bikram's iPhone";
const char* password = "f7krau***g7l";

const char* host = "ec2-54-244-202-56.us-west-2.compute.amazonaws.com";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

void setup() {
  Wire.begin(); 
InitDHT();
Serial.begin(9600);
delay(300);
pinMode(3,INPUT); 
Serial.println("Humidity and temperature\n\n");
delay(700);

  Serial.begin(115200);
  delay(10);

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

  //***************************************************************************************************

  //for light sensor
   int i; 
  
  uint16_t val=0; 
  
  BH1750_Init(BH1750address);  
  
  delay(200); 
  
  if(2==BH1750_Read(BH1750address)) 
  
  { 
  
  val=((buff[0]<<8)|buff[1])/1.2; 
  
  Serial.print(val,DEC); //valÊ®½øÖÆÊä³ö
  
  Serial.println("[lx]"); 
  
  } 
  
  delay(150); 

  
  
  
  //**********************************************************
   int val1,val_old;
 val=digitalRead(3); 
 //digitalWrite(13,val1); 
 val_old=1023-analogRead(1);
 Serial.print("Moisture Sensor Value:");
 Serial.println(map(val_old, 0, 1023, 0, 100)); 
 delay(100);
 
  ReadDHT();
  switch (bGlobalErr){
     case 0:
 Serial.print("Current humdity = ");
 Serial.print(dht_dat[0], DEC);
 Serial.print(".");
 Serial.print(dht_dat[1], DEC);
 Serial.print("%  ");
 Serial.print("temperature = ");
 Serial.print(dht_dat[2], DEC);
 Serial.print(".");
 Serial.print(dht_dat[3], DEC);
 Serial.println("C  ");
        break;
     case 1:
        Serial.println("Error 1: DHT start condition 1 not met.");
        break;
     case 2:
        Serial.println("Error 2: DHT start condition 2 not met.");
        break;
     case 3:
        Serial.println("Error 3: DHT checksum error.");
        break;
     default:
        Serial.println("Error: Unrecognized code encountered.");
        break;
      }
  delay(800);
}

void InitDHT(){
   pinMode(dht_dpin,OUTPUT);
        digitalWrite(dht_dpin,HIGH);
}

void ReadDHT(){
bGlobalErr=0;
byte dht_in;
byte i;
digitalWrite(dht_dpin,LOW);
delay(20);

digitalWrite(dht_dpin,HIGH);
delayMicroseconds(40);
pinMode(dht_dpin,INPUT);
//delayMicroseconds(40);
dht_in=digitalRead(dht_dpin);

if(dht_in){
   bGlobalErr=1;
   return;
   }
delayMicroseconds(80);
dht_in=digitalRead(dht_dpin);

if(!dht_in){
   bGlobalErr=2;
   return;
   }
delayMicroseconds(80);
for (i=0; i<5; i++)
   dht_dat[i] = read_dht_dat();
pinMode(dht_dpin,OUTPUT);
digitalWrite(dht_dpin,HIGH);
byte dht_check_sum =
       dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3];
if(dht_dat[4]!= dht_check_sum)
   {bGlobalErr=3;}
};

byte read_dht_dat(){
  byte i = 0;
  byte result=0;
  for(i=0; i< 8; i++){
      while(digitalRead(dht_dpin)==LOW);
      delayMicroseconds(30);
      if (digitalRead(dht_dpin)==HIGH)
     result |=(1<<(7-i));
    while (digitalRead(dht_dpin)==HIGH);
    }
  return result;
}


  void BH1750_Init(int address) 
  
  { 
  
  Wire.beginTransmission(address);  
  
  Wire.write(0x10); 
  
  Wire.endTransmission(); 
  
  }


  
   int BH1750_Read(int address)  
  
  { 
  
  int i=0; 
  
  Wire.beginTransmission(address); 
  
  Wire.requestFrom(address, 2);  
  while(Wire.available())  
  
  { 
  
  buff[i] = Wire.read();  
  
  i++; 
  
  } 
  
  Wire.endTransmission();  
  
  return i; 
  
  } 
  //******************************************************************************************
  delay(5000);
  ++value;

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
  String url = "/addSensorData";
  url += "?t=";
  url += temperature;
  url += "&m=";
  url += moisture;
  url += "&h=";
  url += humidity;
  url += "&l=";
  url += light;

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

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}

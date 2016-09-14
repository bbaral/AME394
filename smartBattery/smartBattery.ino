

// pins for the LEDs:
const int p1 = 2;
const int p2 = 3;
const int p3 = 4;
const int p4 = 5;
const int p5 = 6;
const int p6 = 7;
const int p7 = 8;
const int p8 = 9;



void setup() {

  // make the pins outputs:
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
  pinMode(p7, OUTPUT);
  pinMode(p8, OUTPUT);

    // initialize serial:
  Serial.begin(9600);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
      int percent = Serial.parseInt();
      if (Serial.read() == '\n') {
          if(percent > 0){digitalWrite(p1, HIGH);}
          else{digitalWrite(p1, LOW);}

          if(percent > 12.5){digitalWrite(p2, HIGH);}
          else{digitalWrite(p2, LOW);}

          if(percent > 25){digitalWrite(p3, HIGH);}
          else{digitalWrite(p3, LOW);}  

                  
          if(percent > 37.5){digitalWrite(p4, HIGH);}
          else{digitalWrite(p4, LOW);}
          
          if(percent > 50){digitalWrite(p5, HIGH);}
          else{digitalWrite(p5, LOW);}
          
          if(percent > 62.5){digitalWrite(p6, HIGH);}
          else{digitalWrite(p6, LOW);}
          
          if(percent > 75){digitalWrite(p7, HIGH);}
          else{digitalWrite(p7, LOW);}
          
          if(percent > 87.5){digitalWrite(p8, HIGH);}
          else{digitalWrite(p8, LOW);}
      }
  }
}

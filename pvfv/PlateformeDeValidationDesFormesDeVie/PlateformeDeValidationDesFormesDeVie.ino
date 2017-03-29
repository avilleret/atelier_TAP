/*
 Plateforme de validation des formes de vie
 Language: Wiring/Arduino

 The circuit:
 * LED attached to digital I/O 4 and 5
 * pushbutton attached to digital I/O 2 and 3

 Created March 29th 2017
 by Antoine Villeret

 */

#define BUZZL_PIN 2
#define BUZZR_PIN 3
#define LEDL_PIN 4
#define LEDR_PIN 5

int buzzL = 0;    // first analog sensor
int buzzR = 0;   // second analog sensor
int ledL = 0;
int ledR = 0;
int i=0;
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  pinMode(BUZZL_PIN, INPUT);   // digital sensor is on digital pin 2
  pinMode(BUZZR_PIN, INPUT);
  digitalWrite(BUZZL_PIN, HIGH); // use internal pull-up resistor
  digitalWrite(BUZZR_PIN, HIGH);

  pinMode(LEDL_PIN, OUTPUT);
  pinMode(LEDR_PIN, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(13, LOW);
  // establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c!=10){
      int pin=LEDL_PIN;
      if ( i == 1 ) pin = LEDR_PIN;
      int level = LOW;
      if (c>48) level = HIGH;
      digitalWrite(pin,level);
      i++;
    } else { 
      i=0;
      Serial.println('A');
    }
  }
 
  buzzL = digitalRead(BUZZL_PIN);
  buzzR = digitalRead(BUZZR_PIN);
  // send sensor values:
  Serial.write(buzzL+48);
  Serial.write(buzzR+48);
  Serial.write('\n');  
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

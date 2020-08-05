//add another sensor and we have it!!!!

//EEprom code:
#include <EEPROM.h>
byte value;
int triggerAddr = 0;
byte trigger;
int multiAddr = 1;
byte multi;

const int ledPin = 2; //for RED indicator LED
const int ledPin2 = 3; //for Green LED - always on
const int ledPin3 = 4; //for first trigger(persistent)
const int beamPin = 8; //beam

int piezoPin = 5;



const int ldrPin = A0;
int num = 0;
long currentMillis = 0;
long previousMillis = 0;
boolean triggered = false;

void setup() {
  //sound check delete:
//  for(int i = 0; i < 20; i++){
//      tone(piezoPin, 1000*i, 5000);
//      delay(5000);
//      tone(piezoPin, 200, 50000);
//     tone(piezoPin, 300000, 500);
//      }
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, LOW);

  pinMode(beamPin, INPUT);
  

  //eeprom code:
  trigger = EEPROM.read(triggerAddr);
  if (trigger > 0) {
    Serial.println("TRIGGERED");
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
    }
  } else {
    //"NO Trigger detected last time"
  }
  multi = EEPROM.read(multiAddr);
  Serial.print("Multi is: ");
  Serial.println(multi);
  multi = 0;
}



void loop() {
  int ldrStatus = analogRead(ldrPin);
  //    Serial.println(ldrStatus);
int reading = digitalRead(beamPin);

  if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!
    if (reading==HIGH) {
      digitalWrite(ledPin, HIGH); //switch on LED
      for(int i = 0; i < 5000; i++){
      tone(piezoPin, 1000*i, 5000);
      tone(piezoPin, 200, 5000);
     tone(piezoPin, 300000, 5000);
      }
     for(int i = 0; i < 20; i++){
      tone(piezoPin, 1000*i, 5000);
      delay(5000);
      tone(piezoPin, 200, 50000);
     tone(piezoPin, 300000, 500);
      }
      triggered = true;
      
      Serial.print("ALERT!! ");
      multi++;
      Serial.println(num++);
      Serial.println(ldrStatus);
      EEPROM.write(multiAddr, multi); //increment multi
      trigger = 1;
      EEPROM.write(triggerAddr, trigger); //write to triggered switch
    } else {
//      digitalWrite(ledPin, LOW); //if you want the LED to switch off after it is triggered. Otherwise the LED stays on. 
    }
    previousMillis = millis();
  }

  if (triggered) {
    digitalWrite(ledPin3, HIGH);
  }

}

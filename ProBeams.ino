
//Read from a commercial IR Beam - set off a piezo buzzer
//code by Tom Hastings
//license GPL v3
const int ledPin = 7;
//const int ledPin = LED_BUILTIN; //for RED indicator LED. Was 2 here..
const int beamPin = 8; //beam
const int PIRPin = 2; //PIR motion sensor - should be pin 10
int piezoPin = 5;
long currentMillis = 0;
long previousMillis = 0;
int val = 0;  // variable to store the sensor status (value)
int reading = 0; //beamPin reading
long alarmLength = 20000;
//save events counter:
int PIREvents = 0;
int beamEvents = 0;
int state = LOW;
//#include "Volume.h" // Include the Volume library

//Volume vol; // Plug your speaker into the default pin for your board type:
// https://github.com/connornishijima/arduino-volume#supported-pins

#include <EEPROM.h>

byte value;
int optionAddr = 0;
byte option;

void setup() {
  //here we read
  option = EEPROM.read(optionAddr);
  option = option + 1;
  if (option >= 2) //2 options only, 0 or 1, you can have as many as you like
    option = 0; // back to 0 if
  EEPROM.write(optionAddr, option); //save the incremented option for next time
  state = LOW;
  //  vol.begin(); // After calling this, delay() and delayMicroseconds will no longer work
  //  // correctly! Instead, use delay() and delayMicroseconds() for
  //  // the correct timing
  //
  //  vol.setMasterVolume(1.00); // Self-explanatory enough, right? Try lowering this value if the speaker is too loud! (0.00 - 1.00)
  //  delay(500);

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  switch (option)
  {
    case 0: //option is 0, beam only
      Serial.println("Beam only here");
      pinMode(beamPin, INPUT);
      //test LED:

      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
      break;
    case 1: //option is 1, PIR and beam
      Serial.println("PIR and Beam here");
      pinMode(PIRPin, INPUT);
      pinMode(beamPin, INPUT);
      //test LED:
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledPin, HIGH);
        delay(200);
        digitalWrite(ledPin, LOW);
        delay(200);
      }
      break;
    default:
      // do nothing
      break;
  }
  delay(2000); //delay for PIR?
}

void loop() {

  switch (option)
  {
    case 0: //option is 0, led off
      beamOnly();
      break;
    case 1: //option is 0, led on
      allOn();
      break;
    default:
      // do nothing
      break;
  }
}
void beamOnly() {
  reading = digitalRead(beamPin);
  if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!
    
    if (reading == HIGH) {
      previousMillis = millis();
      digitalWrite(ledPin, HIGH); //switch on LED if triggered
      Serial.println("beam triggered");
      beamEvents++;
      Serial.print(", beamEvents: ");
          Serial.println(beamEvents);
      longTone();
    } else {
      //      digitalWrite(ledPin, LOW); //if you want the LED to switch off after it is triggered. Otherwise the LED stays on.
    }
    

  }
  /*
    reading = digitalRead(beamPin);
    val = digitalRead(PIRPin);
    if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!
      if (reading == HIGH) {
        previousMillis = millis();
        if (state == LOW) {
          //BEAM:
          beamEvents++;
          Serial.print("Motion detected! PIREvents: " );
          Serial.print(PIREvents);
          Serial.print(", beamEvents: ");
          Serial.println(beamEvents);
          longTone(); //disabled for test only
          state = HIGH; //disabled for test only
        }
        digitalWrite(ledPin, HIGH); //switch on LED if triggered
      } else {
        if (state == HIGH) {
          Serial.println("Motion stopped!");
          state = LOW;
          //        if (millis() - previousMillis > alarmLength) { //delay before switching off
          //          state = LOW;       // update variable state to LOW
          //        }
        }
        //        Serial.println("low");
        digitalWrite(ledPin, LOW); //if you want the LED to switch off after it is triggered. Otherwise the LED stays on.
      }

    }
  */
}

void allOn() {
  reading = digitalRead(beamPin);
  val = digitalRead(PIRPin);
  if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!
    if (reading == HIGH || val == HIGH) {
      previousMillis = millis();
      if (state == LOW) {
        //BEAM:

        if (reading == HIGH) {
          beamEvents++;
          Serial.print("Motion detected! PIREvents: " );
          Serial.print(PIREvents);
          Serial.print(", beamEvents: ");
          Serial.println(beamEvents);
          longTone(); //disabled for test only
          state = HIGH; //disabled for test only
        }
        // PIR:
        if (val == HIGH) {
          PIREvents++;
          Serial.print("Motion detected! PIREvents: " );
          Serial.print(PIREvents);
          Serial.print(", beamEvents: ");
          Serial.println(beamEvents);
          shortTone(); //- the right one for PIR
          //           testTone(); //testing
          //           state = HIGH; //causing the beam not to work here? needs to be disabled, only enable for testing
        }

        //        if (reading == HIGH && val == HIGH) {
        //          Serial.println("BEAM AND PIR!!!");
        //          for (int i = 0; i < 5; i++) {
        //            digitalWrite(ledPin, HIGH);
        //            delay(100);
        //            digitalWrite(ledPin, LOW);
        //          }
        //        }


        //        state = HIGH;       // update variable state to HIGH
      }

      //      Serial.println("high");
      digitalWrite(ledPin, HIGH); //switch on LED if triggered



    } else {
      if (state == HIGH) {
        Serial.println("Motion stopped!");
        state = LOW;
        //        if (millis() - previousMillis > alarmLength) { //delay before switching off
        //          state = LOW;       // update variable state to LOW
        //        }
      }
      //        Serial.println("low");
      digitalWrite(ledPin, LOW); //if you want the LED to switch off after it is triggered. Otherwise the LED stays on.
    }

  }
}
void testTone() {
  for (int i = 0; i < 100; i++) {
    tone(piezoPin, 1000 * i, 5000);
    tone(piezoPin, 200, 5000);
    tone(piezoPin, 300000, 5000);
  }
}

void shortTone() {
  for (int i = 0; i < 5000; i++) {
    tone(piezoPin, 1000 * i, 5000);
    tone(piezoPin, 200, 5000);
    tone(piezoPin, 300000, 5000);
  }
}
void longTone() {
  for (int i = 0; i < 20; i++) {
    tone(piezoPin, 1000 * i, 5000);
    delay(5000);
    tone(piezoPin, 200, 50000);
    tone(piezoPin, 300000, 500);
  }
}

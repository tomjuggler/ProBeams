
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
void setup() {
  state = LOW;
  //  vol.begin(); // After calling this, delay() and delayMicroseconds will no longer work
  //  // correctly! Instead, use delay() and delayMicroseconds() for
  //  // the correct timing
  //
  //  vol.setMasterVolume(1.00); // Self-explanatory enough, right? Try lowering this value if the speaker is too loud! (0.00 - 1.00)
  //  delay(500);

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(beamPin, INPUT);
  pinMode(PIRPin, INPUT);
  //test LED:
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
//  delay(1000); //delay start for PIR?
}

void loop() {
  reading = digitalRead(beamPin);
  val = digitalRead(PIRPin);
  if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!

//  if (reading == HIGH){
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
//void wolfWhistle() {
//  int f = 122; // starting frequency
//  int v = 0;   // starting volume
//  while (f < 6000) {  // slide up to 4000Hz
//    vol.tone(f, v);
//    v = 255 * (f / 6000.00);
//    f += 25;
//    delay(1);
//  }
//  vol.noTone();
//  delay(100); // wait a moment
//  f = 122; // starting frequency
//  v = 0;   // starting volume
//  while (f < 3000) { // slide up to 3000Hz
//    vol.tone(f, v);
//    v = 255 * (f / 4000.00);
//    f += 25;
//    delay(2);
//  }
//  while (f > 125) { // slide down to 125Hz
//    vol.tone(f, v);
//    v = 255 * (f / 4000.00);
//    f -= 25;
//    delay(2);
//  }
//  vol.noTone(); // end tone production
//}

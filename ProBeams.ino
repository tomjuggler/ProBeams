
//Read from a commercial IR Beam - set off a piezo buzzer
//code by Tom Hastings
//license GPL v3

const int ledPin = LED_BUILTIN; //for RED indicator LED. Was 2 here..
const int beamPin = 8; //beam
const int PIRPin = 2; //PIR motion sensor - should be pin 10
int piezoPin = 5;
long currentMillis = 0;
long previousMillis = 0;
int val = 0;  // variable to store the sensor status (value)
int reading = 0; //beamPin reading

//save events counter:
int PIREvents = 0;
int beamEvents = 0;
int state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(beamPin, INPUT);
  pinMode(PIRPin, INPUT);
  //test LED:
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  reading = digitalRead(beamPin);
  val = digitalRead(PIRPin);
  if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!
    if (reading == HIGH || val == HIGH) {
      if (state == LOW) {
        if (reading == HIGH) {
          beamEvents++;
        }
        if (val == HIGH) {
          PIREvents++;
        }
        Serial.print("Motion detected! PIR: " );
        Serial.print(PIREvents);
        Serial.print(", beamEvents: ");
        Serial.println(beamEvents);

        state = HIGH;       // update variable state to HIGH
      }

      //      Serial.println("high");
      digitalWrite(ledPin, HIGH); //switch on LED if triggered
      /*
        for(int i = 0; i < 5000; i++){
        tone(piezoPin, 1000*i, 5000);
        tone(piezoPin, 200, 5000);
        tone(piezoPin, 300000, 5000);
        }
        //crazy long alarm beeps:
        for(int i = 0; i < 20; i++){
        tone(piezoPin, 1000*i, 5000);
        delay(5000);
        tone(piezoPin, 200, 50000);
        tone(piezoPin, 300000, 500);
        }
      */
    } else {
      if (state == HIGH) {
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
      }
      //        Serial.println("low");
      digitalWrite(ledPin, LOW); //if you want the LED to switch off after it is triggered. Otherwise the LED stays on.
    }
    previousMillis = millis();
  }
}

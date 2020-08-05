
//Read from a commercial IR Beam - set off a piezo buzzer
//code by Tom Hastings
//license GPL v3

const int ledPin = 2; //for RED indicator LED
const int beamPin = 8; //beam
int piezoPin = 5;
long currentMillis = 0;
long previousMillis = 0;

void setup() {
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);
  pinMode(beamPin, INPUT);
  //test LED:  
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
    }  
}

void loop() {
int reading = digitalRead(beamPin);
  if (millis() - previousMillis > 50) { //only check every 50ms? seems to work great!
    if (reading==HIGH) {
      digitalWrite(ledPin, HIGH); //switch on LED if triggered
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
       } else {
//      digitalWrite(ledPin, LOW); //if you want the LED to switch off after it is triggered. Otherwise the LED stays on. 
    }
    previousMillis = millis();
  }
}

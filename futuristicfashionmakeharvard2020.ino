/*
 * MAKE HARVARD MAKEATHON 2020 02/01/2020 - 02/02/2020
 * Written by Charlie DeLorey, an amalgamation of multiple
 * code fragments for using an Adafruit ultrasonic sensor
 * and 4 LEDs controlled with button toggle input.
 * 
 * 
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */
int inPin = 2;         // the number of the button input pin

// COLOR PINS
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int yellowPin = 8;

int outPin = 11;

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
int previousPin = 8; 
int buttonPressCount = 0;
int numLED = 4;
int distfrombehind = 30; // distance measured in cm

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

#define trigPin 13
#define echoPin 12
#define led 7          // LED that indicates something within 'distfrombehind' cm from
                      //  the back of the wearer.

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), buttonMonitor, CHANGE);
}

void loop() {
   // uncomment the next two lines to cycle through the LEDs automatically, IF THE BUTTON STOPS WORKING
   // ALSO, COMMENT OUT line 56
   // int s = 5;
   //cycleMoods(s);
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < distfrombehind) {  // This is where the LED On/Off happens, this is in cm!
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
}
  else {
    digitalWrite(led,LOW);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

void buttonMonitor() {
    reading = digitalRead(inPin);
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    //Serial.println("~~~~~~~~BUTTON PRESSED!!!!!~~~~~~~");
    if (state == HIGH) {
      state = LOW;
    if (outPin == 8) {
    outPin = 11;
    previousPin = 8;
    } else
    previousPin = outPin;
    outPin--;
    } else {
      state = HIGH;
    }
        time = millis();
  }
  setOff(outPin);
  digitalWrite(outPin, state);
  previous = reading;
}

// Function for cycling through the four colors, for testing/display purposes if the button doesn't work
void cycleMoods(int sec) {
  digitalWrite(11, HIGH);
  delay(sec * 1000);
  digitalWrite(11, LOW);
  delay(1000);
  digitalWrite(10, HIGH);
  delay(sec * 1000);
  digitalWrite(10, LOW);
  delay(1000);
  digitalWrite(9, HIGH);
  delay(sec * 1000);
  digitalWrite(9, LOW);
  delay(1000);
  digitalWrite(8, HIGH);
  delay(sec * 1000);
  digitalWrite(8, LOW);
  delay(1000);
}

// Function for clearing the other 3 LEDs when we only want one on
void setOff(int currOn) {
  if (currOn == 11) {
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
  }
    else if (currOn == 10) {
    digitalWrite(11, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
  }
    else if (currOn == 9) {
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(8, LOW);
  }
    else {
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
  }
}

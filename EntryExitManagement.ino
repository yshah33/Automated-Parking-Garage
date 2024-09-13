#include <Wire.h>
#include <Servo.h>

// LED light pins
const int light_red = 12;
const int light_green = 13;

// Ultrasonic sensor pins
const int triggerPin1 = 2; 
const int triggerPin2 = 4; 
const int echoPin1 = 3; 
const int echoPin2 = 5;

// Servo motor control pin
const int enterPin = 9; 
const int exitPin = 10;
int buzzPin = 7;

// Max distance for ultrasonic sensor (in cm)
const unsigned int maxDistance = 10;

// Car counter
int carCounter = 0;

// Servo motor object
Servo enterServo; 
Servo exitServo;

// Gate positions
const int gateOpenPosition = 90; 
const int gateClosedPosition = 0;

void setup() { 
  Serial.begin(9600);
  //added
  Wire.begin(0x04); // Arduino 1 is the slave with address 1 
  Wire.onReceive(receiveEvent);
  Serial.print("car when received: "); 
  Serial.println(carCounter);

  pinMode(light_red, OUTPUT); 
  pinMode(light_green, OUTPUT);
  pinMode(triggerPin1, OUTPUT); 
  
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  
  pinMode(buzzPin, OUTPUT); 
  digitalWrite(buzzPin, LOW);
  // Attach the servo motor to its control pin
  enterServo.attach(enterPin); 
  exitServo.attach(exitPin);
  
  // Initialize gate to closed position
  entryCloseGate();

  exitCloseGate(); 
}

void loop() { 
  reset();
  // Check ultrasonic sensor for vehicle presence
  bool vehicleDetectedEntrance = measureDistance(triggerPin1, echoPin1) < maxDistance;
  if (vehicleDetectedEntrance) { 
    if (carCounter < 3 ) {
      Serial.print("car counter "); 
      Serial.println(carCounter);
      digitalWrite(light_green, HIGH);
      entryOpenGate(); 
    }
    else {
      digitalWrite(light_red, HIGH); 
    }
    delay(2000); // Delay to allow the car to pass 
  }
  bool vehicleDetectedExit = measureDistance(triggerPin2, echoPin2) < maxDistance;
  if (vehicleDetectedExit && carCounter >= 0) { 
    exitOpenGate();
    digitalWrite(buzzPin, HIGH);
    tone(buzzPin, 999);
    delay(2000); 
  }
  // Add a short delay to prevent bouncing
  delay(100); 
}

void reset() {
  // Ensure the gate is closed if no vehicle is detected entryCloseGate();
  exitCloseGate();
  // LED light to default
  digitalWrite(light_red, LOW); 
  digitalWrite(light_green, LOW); 
}

void receiveEvent(int temp) { 
  while (Wire.available()) {
    int data = Wire.read();
    // Process received data from Arduino 2
    carCounter = data; 
  }
}

long measureDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(triggerPin, HIGH); 
  delayMicroseconds(10); 
  
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH); 
  long distance = duration * 0.034 / 2; 
  
  return distance;
}

void entryOpenGate() { 
  enterServo.write(gateOpenPosition);
}

void entryCloseGate() {
  enterServo.write(gateClosedPosition); 
}

void exitOpenGate() { 
  exitServo.write(gateOpenPosition);
}

void exitCloseGate() { 
  exitServo.write(gateClosedPosition); 
  noTone(buzzPin);
}

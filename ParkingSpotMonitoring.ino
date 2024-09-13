#include <NewPing.h>
#include <Wire.h>

const int Arduino1Address = 0x04; // Arduino 1 address 
const int Arduino3Address = 0x05; // Arduino 3 address

// Occupied parking spots for lights 
int carSpaceOcc1 = 13; //spot 1
int carSpaceOcc2 = 12; // spot 2
int carSpaceOcc3 = 11; //spot 3
 
// Unoccupied parking spots for lights 
int carSpaceUnocc1 = 10; //spot 1
int carSpaceUnocc2 = 9; //spot 2
int carSpaceUnocc3 = 8; // spot 3

// three sensor for each lot
const int echoPin1 = 7; 
const int echoPin2 = 6; 
const int echoPin3 = 5;

const int triggerPin1 = 3; 
const int triggerPin2 = 2; 
const int triggerPin3 = 4;

bool isSpot1Occupied = false; 
bool isSpot2Occupied = false; 
bool isSpot3Occupied = false;

const unsigned int maxDistance = 10; 
int availableParking = 3;
int carCounter = 0;

NewPing sensor1(triggerPin1, echoPin1, maxDistance); 
NewPing sensor2(triggerPin2, echoPin2, maxDistance); 
NewPing sensor3(triggerPin3, echoPin3, maxDistance);

void setup() { 
  Serial.begin(9600); 
  Wire.begin(); // added
  pinMode(carSpaceUnocc1,OUTPUT); 
  pinMode(carSpaceUnocc2,OUTPUT); 
  pinMode(carSpaceUnocc3,OUTPUT);
  
  pinMode(carSpaceOcc1,OUTPUT); 
  pinMode(carSpaceOcc2,OUTPUT);
  pinMode(carSpaceOcc3,OUTPUT); 
}

void loop() {
  reset();
  bool vehicle1Detected = checkUltrasonicSensor(sensor1); 
  bool vehicle2Detected = checkUltrasonicSensor(sensor2); 
  bool vehicle3Detected = checkUltrasonicSensor(sensor3);

  updateParkingStatus(sensor1, carSpaceOcc1, carSpaceUnocc1, isSpot1Occupied); 
  updateParkingStatus(sensor2, carSpaceOcc2, carSpaceUnocc2, isSpot2Occupied); 
  updateParkingStatus(sensor3, carSpaceOcc3, carSpaceUnocc3, isSpot3Occupied);
  
  if(vehicle1Detected) { 
    digitalWrite(carSpaceOcc1, HIGH); 
    Wire.beginTransmission(Arduino3Address);
    
    // Wire.write((byte)availableParking); // Cast to byte if needed
    Wire.write('x');
    Wire.endTransmission(); 
  }
  else{
    digitalWrite(carSpaceUnocc1, HIGH);
  }
  
  if(vehicle2Detected){ 
    digitalWrite(carSpaceOcc2, HIGH);
  } 
  else{
    digitalWrite(carSpaceUnocc2, HIGH); 
  }
  if(vehicle3Detected){ 
    digitalWrite(carSpaceOcc3, HIGH);
  } 
  else{
    digitalWrite(carSpaceUnocc3, HIGH); 
  }
  
  // Send available parking count to Arduino 1
  Wire.beginTransmission(Arduino1Address); 
  Wire.write(availableParking); // Cast to byte if needed 
  Wire.endTransmission();

  // Send available parking count to Arduino 3
  Wire.beginTransmission(Arduino3Address); 
  Wire.write(availableParking); // Cast to byte if needed 
  Wire.endTransmission();
  
  delay(1000); 
}

void updateParkingStatus(NewPing &sensor, int occupiedPin, int unoccupiedPin, bool &isOccupied) {
  bool vehicleDetected = checkUltrasonicSensor(sensor);
  
  if (vehicleDetected && !isOccupied) { 
    digitalWrite(occupiedPin, HIGH); 
    digitalWrite(unoccupiedPin, LOW); 
    isOccupied = true; 
    availableParking--;
  }
  else if (!vehicleDetected && isOccupied) {
    digitalWrite(occupiedPin, LOW); 
    digitalWrite(unoccupiedPin, HIGH); 
    isOccupied = false; 
    availableParking++;
  } 
}

void reset() { 
  digitalWrite(carSpaceOcc1, LOW); 
  digitalWrite(carSpaceUnocc1, LOW);
  digitalWrite(carSpaceOcc2, LOW); 
  
  digitalWrite(carSpaceUnocc2, LOW); 
  digitalWrite(carSpaceOcc3, LOW); 
  digitalWrite(carSpaceUnocc3, LOW); 
}

bool checkUltrasonicSensor(NewPing &sensor) { 
  unsigned int uS = sensor.ping();
  unsigned int distance = uS / US_ROUNDTRIP_CM; 
  return (distance > 0 && distance < 100);
}

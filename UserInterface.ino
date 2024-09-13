#include <LiquidCrystal.h> 
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
int receivedData = 0;

void setup() { 
  Serial.begin(9600); 
  lcd.begin(16, 2); 
  Wire.begin(0x05);
  Wire.onReceive(receiveEvent); 
}

void loop() { 
  delay(100);
}

void receiveEvent(int how) { 
  while (Wire.available()) {
    receivedData = Wire.read();
    printData(); 
  }
}

void printData () { 
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Spot Free: ");
  lcd.print(receivedData); 
}

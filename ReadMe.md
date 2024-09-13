# Automated Car Parking Garage System

## Abstract

This Arduino-based project automates a car parking garage system to efficiently manage vehicle entry and exit. By using sensors, LED lights, and multiple Arduino boards, the system detects vehicles, indicates parking spot availability, and controls gate access. It employs three Arduinos to handle Entry/Exit management, Parking Spot monitoring, and User Interface, communicating via Ethernet to ensure real-time data exchange and responsiveness.

## Detailed Project Overview

### Overall Description

The Automated Car Parking Garage System is designed to manage vehicle entry and exit efficiently. It utilizes sensors to detect vehicle presence and parking spot availability. Each parking spot is equipped with an LED light to show whether it is vacant (green) or occupied (red). The system uses three Arduino boards:

1. **Entry/Exit Management**: Controls vehicle access based on parking spot availability.
2. **Parking Spot Monitoring**: Manages spot status and LED indicators.
3. **User Interface (Dashboard)**: Displays parking spot availability and locations.

### Initial Project Design

#### Arduino 1: Entry/Exit Management
- **Vehicle Detection**: Uses 2 ultrasonic sensors at the entrance and exit.
- **Gate Control**: Opens or closes the gate based on parking availability. Red LED indicates a full garage.
- **Communication**: Shares parking availability data with Arduino 2 and 3.

#### Arduino 2: Parking Spot Monitoring
- **Spot Detection**: Uses ultrasonic sensors above each parking spot.
- **LED Control**: Manages LEDs for each parking spot based on occupancy.
- **Availability Tracking**: Communicates available spot data to Arduino 1 and 3.

#### Arduino 3: User Interface (Dashboard)
- **Display Data**: Uses an LCD to show available parking spots and their locations.
- **Communication**: Receives data from Arduino 2 and updates the display.

### Final Plan for Use and Communication

The system uses I2C communication with Arduino 2 as the master and Arduinos 1 and 3 as slaves:
- **Arduino 2 (Master)**: Monitors parking status, updates Arduino 1 and 3.
- **Arduino 1 (Slave)**: Controls gate access based on data from Arduino 2.
- **Arduino 3 (Slave)**: Displays parking status on the user interface.

## Final Project Design

### Expected Inputs/Outputs

**Input Devices:**
- **Ultrasonic Sensors**: Detect vehicle presence.
- **Push Button**: Displays available spots on LCD when pressed.

**Output Devices:**
- **LED Lights**: Indicate parking spot availability (green/red).
- **LCD Dashboard**: Shows the number of available spots.
- **Servo Motor**: Controls gate movement.
- **Buzzer**: Alerts when a vehicle exits.

### Final Description

Our project, the Automated Parking Garage System, integrates ultrasonic sensors with Arduino boards to manage vehicle entry and exit efficiently. It uses real-time communication to guide drivers to available spots and handle full capacity scenarios effectively. This system improves the parking experience, reduces congestion, and optimizes space utilization.

### Discussion on Building the Project

1. **Gathering Materials**: Obtain Arduino UNO boards, ultrasonic sensors, LEDs, LCD screen, servo motors, buzzer, pushbuttons, wires, and resistors.
2. **Initial Setup**: Configure the Arduino IDE for programming each board according to its role.
3. **Sensor Integration**: Install sensors at entrances and above parking spots.
4. **LED and LCD Implementation**: Connect LEDs and an LCD for status indication and user interface.
5. **Servo Motor and Buzzer Setup**: Install servo motors for gate control and a buzzer for exit alerts.
6. **Programming and Networking**: Write and upload code to Arduinos, setting up I2C communication.
7. **Testing and Calibration**: Test components individually and as a whole, calibrate as needed.
8. **Final Assembly and Integration**: Assemble and secure all components, ensure system responsiveness.

### User Guide

1. **Vehicle Detection**: Sensors at the garage entrance detect vehicles and check for available spots.
2. **Gate Management**: Opens the gate if spots are available; otherwise, the gate remains closed, and red LEDs indicate full capacity.
3. **Parking Spot Guidance**: Green LEDs guide drivers to empty spots.
4. **Dashboard Information**: LCD shows the number of available spots and their locations.
5. **Exiting the Garage**: Exit sensors detect vehicles, open the gate, and sound the buzzer. Updates parking spot availability.
6. **Manual Interaction**: Press the push button to display available spots on the LCD.

### Final List of Materials

- 3x Arduino UNO
- 3x Breadboards
- 1x LED Screen
- 1x Potentiometer
- 1x Buzzer
- 1x Pushbutton
- 8x LEDs
- 2x Servo Motors or Stepper Motors
- 5x Ultrasonic Sensors
- 3x LCD Screens
- Multiple Wires and Resistors

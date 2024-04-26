#include <BluetoothSerial.h>

// Define motor pins
const int motor1A = 32 ;
const int motor1B = 23;
const int motor1C = 33;
const int motor1D = 25;

const int motor2A = 27 ;
const int motor2B = 12;
const int motor2C = 13;
const int motor2D = 2;

// Bluetooth
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Car"); // Bluetooth device name

  // Initialize motor pins for motor drive 1
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor1C, OUTPUT);
  pinMode(motor1D, OUTPUT);
  
 // Initialize motor pins for motor drive 2
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2C, OUTPUT);
  pinMode(motor2D, OUTPUT);

  Serial.println("Bluetooth Car Initialized");
}
    void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();

    // Move forward
    if (command == 'F') {
      moveForward();
    }
    // Move backward
    else if (command == 'B') {
      moveBackward();
    }
    // Turn left
    else if (command == 'L') {
      turnLeft();
    }
    // Turn right
    else if (command == 'R') {
      turnRight();
    }
    // Stop
    else if (command == 'S') {
      stopCar();
    }
  }
}

// Functions to control the car
void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, HIGH);
  digitalWrite(motor1D, LOW);
  
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  digitalWrite(motor2C, LOW);
  digitalWrite(motor2D, HIGH);
}

void moveBackward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1C, LOW);
  digitalWrite(motor1D, HIGH);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, HIGH);
  digitalWrite(motor2D, LOW);
}

void turnLeft() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, LOW);
  digitalWrite(motor1D, HIGH);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  digitalWrite(motor2C, HIGH);
  digitalWrite(motor2D, LOW);
}

void turnRight() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1C, HIGH);
  digitalWrite(motor1D, LOW);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, LOW);
  digitalWrite(motor2D, HIGH);
}


void forwardright(){
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, HIGH);
  digitalWrite(motor1D, LOW);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, LOW);
  digitalWrite(motor2D, HIGH);
  }
void forwardLeft() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, LOW);
  digitalWrite(motor1D, LOW);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  digitalWrite(motor2C, LOW);
  digitalWrite(motor2D, LOW);
}

void backwardLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor1C, LOW);
  digitalWrite(motor1D, LOW);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, LOW);
  digitalWrite(motor2D, LOW);
}

void backdright() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, LOW);
  digitalWrite(motor1D, HIGH);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, HIGH);
  digitalWrite(motor2D, LOW);
}

void stopCar() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor1C, LOW);
  digitalWrite(motor1D, LOW);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  digitalWrite(motor2C, LOW);
  digitalWrite(motor2D, LOW);
}

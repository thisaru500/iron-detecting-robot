#include "BluetoothSerial.h"

#define LED_PIN 5 // if iron found that led will turn off
int ironsensorpin1 = 4;
int ironsensorpin2 = 36;
bool ironFound = false;

const int motor1A = 32;
const int motor1B = 23;
const int motor1C = 33;
const int motor1D = 25;

const int motor2A = 27;
const int motor2B = 12;
const int motor2C = 13;
const int motor2D = 2;

// Bluetooth
BluetoothSerial SerialBT;

// Function prototypes
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void forwardRight();
void forwardLeft();
void backwardRight();
void backwardLeft();
void stopCar();
void checkIronState();
void sendTextMessage(String message);

// Speed control
int speed = 255; // Default speed (range from 0 to 255)

// Pins for PWM
const int pwmChannel1A = 0;
const int pwmChannel1B = 1;
const int pwmChannel2A = 2;
const int pwmChannel2B = 3;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Car"); // Bluetooth device name

  pinMode(ironsensorpin1, INPUT);
  pinMode(ironsensorpin2, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Turn on LED initially

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

  // Set up PWM channels
  ledcSetup(pwmChannel1A, 5000, 8);
  ledcSetup(pwmChannel1B, 5000, 8);
  ledcSetup(pwmChannel2A, 5000, 8);
  ledcSetup(pwmChannel2B, 5000, 8);
  
  // Attach PWM channels to pins
  ledcAttachPin(motor1A, pwmChannel1A);
  ledcAttachPin(motor1B, pwmChannel1B);
  ledcAttachPin(motor2A, pwmChannel2A);
  ledcAttachPin(motor2B, pwmChannel2B);

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
    // Move forward right
    else if (command == 'G') {
      forwardRight();
    }
    // Move forward left
    else if (command == 'I') {
      forwardLeft();
    }
    // Move backward right
    else if (command == 'J') {
      backwardRight();
    }
    // Move backward left
    else if (command == 'H') {
      backwardLeft();
    }
    // Increase speed
    else if (command == '+') {
      speed = min(255, speed + 10);
      Serial.println("Speed: " + String(speed));
    }
    // Decrease speed
    else if (command == '-') {
      speed = max(0, speed - 10);
      Serial.println("Speed: " + String(speed));
    }
  }
  checkIronState();
}

// Functions to control the car
void moveForward() {
  ledcWrite(pwmChannel1A, speed);
  ledcWrite(pwmChannel1B, 0);
  ledcWrite(pwmChannel2A, 0);
  ledcWrite(pwmChannel2B, speed);
}

void moveBackward() {
  ledcWrite(pwmChannel1A, 0);
  ledcWrite(pwmChannel1B, speed);
  ledcWrite(pwmChannel2A, speed);
  ledcWrite(pwmChannel2B, 0);
}

void turnLeft() {
  ledcWrite(pwmChannel1A, speed);
  ledcWrite(pwmChannel1B, 0);
  ledcWrite(pwmChannel2A, speed);
  ledcWrite(pwmChannel2B, 0);
}

void turnRight() {
  ledcWrite(pwmChannel1A, 0);
  ledcWrite(pwmChannel1B, speed);
  ledcWrite(pwmChannel2A, 0);
  ledcWrite(pwmChannel2B, speed);
}

void forwardRight() {
  ledcWrite(pwmChannel1A, speed / 2);
  ledcWrite(pwmChannel1B, 0);
  ledcWrite(pwmChannel2A, 0);
  ledcWrite(pwmChannel2B, speed);
}

void forwardLeft() {
  ledcWrite(pwmChannel1A, speed);
  ledcWrite(pwmChannel1B, 0);
  ledcWrite(pwmChannel2A, 0);
  ledcWrite(pwmChannel2B, speed / 2);
}

void backwardRight() {
  ledcWrite(pwmChannel1A, 0);
  ledcWrite(pwmChannel1B, speed / 2);
  ledcWrite(pwmChannel2A, speed);
  ledcWrite(pwmChannel2B, 0);
}

void backwardLeft() {
  ledcWrite(pwmChannel1A, 0);
  ledcWrite(pwmChannel1B, speed);
  ledcWrite(pwmChannel2A, speed / 2);
  ledcWrite(pwmChannel2B, 0);
}

void stopCar() {
  ledcWrite(pwmChannel1A, 0);
  ledcWrite(pwmChannel1B, 0);
  ledcWrite(pwmChannel2A, 0);
  ledcWrite(pwmChannel2B, 0);
}

// Function to check the state of the iron sensors
void checkIronState() {
  int ironState1 = digitalRead(ironsensorpin1);
  int ironState2 = digitalRead(ironsensorpin2);

  if (ironState1 == HIGH || ironState2 == HIGH) {
    // Iron is found
    if (!ironFound) {
      ironFound = true;
      stopCar();
      sendTextMessage("Iron is found");
      digitalWrite(LED_PIN, LOW); // Turn off LED
      delay(2000);
    }
  } else {
    // Iron is not found
    if (ironFound) {
      ironFound = false;
      digitalWrite(LED_PIN, HIGH); // Turn on LED
    }
  }
}

void sendTextMessage(String message) {
  // Code to send a text message via GSM module goes here
  Serial.println(message);
}

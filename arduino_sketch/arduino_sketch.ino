
#include <SoftwareSerial.h>

//Engine
#define MOTOR1_SPEED 4
//right
#define MOTOR1_IN1 8
#define MOTOR1_IN2 7
//left
#define MOTOR1_IN3 6
#define MOTOR1_IN4 5

//bluetooth
#define BT_RX_PIN 10
#define BT_TX_PIN 11

SoftwareSerial mySerialBlueTooth(BT_RX_PIN, BT_TX_PIN);  // RX, TX
char command;                                            // Stores response of bluetooth device
// which simply allows \n between each
// response.

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("Type AT commands!");
  // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.
  mySerialBlueTooth.begin(9600);

  pinMode(MOTOR1_SPEED, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR1_IN3, OUTPUT);
  pinMode(MOTOR1_IN4, OUTPUT);
}

void loop() {
  // Read device output if available.
  if (mySerialBlueTooth.available()) {
    Serial.println("In Output from BT");

    command = mySerialBlueTooth.read();  // legge 1 carattere
    Serial.println(command);



    //here logic to control engine
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        turn_left();
        break;
      case 'R':
        turn_right();
        break;
      case 'Z':
        motor_stop();
        break;
    }
    command = "";  // No repeats
  }

  // Read user input if available.
  if (mySerialBlueTooth.available()) {
    Serial.println("In Input from BT");
    int res = Serial.read();
    Serial.println(res);
    delay(10);  // The DELAY!
    mySerialBlueTooth.write(res);
  }
}


void motor_clockwise_right() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
}
void motor_clockwise_left() {
  digitalWrite(MOTOR1_IN4, LOW);
  digitalWrite(MOTOR1_IN3, HIGH);
}
void motor_counterclockwise_left() {
  digitalWrite(MOTOR1_IN3, LOW);
  digitalWrite(MOTOR1_IN4, HIGH);
}
void motor_counterclockwise_right() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
}
void motor_stop() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR1_IN3, LOW);
  digitalWrite(MOTOR1_IN4, LOW);
}
void forward() {
  motor_clockwise_right();
  motor_clockwise_left();
}
void backward() {
  motor_counterclockwise_right();
  motor_counterclockwise_left();
}
void stop_right() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
}
void stop_left() {
  digitalWrite(MOTOR1_IN3, LOW);
  digitalWrite(MOTOR1_IN4, LOW);
}
void turn_right() {
  stop_left();
  motor_clockwise_right();
}
void turn_left() {
  stop_right();
  motor_clockwise_left();
}


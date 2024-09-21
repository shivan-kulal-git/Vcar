#include <AFMotor.h>

// Pin definitions
#define Echo A0
#define Trig A1
#define RedLED 8
#define GreenLED 7

// Constants
const int motorSpeed = 150;       // Default motor speed
const int turnSpeed = 255;        // Speed for turns
const int distanceThreshold = 20; // Distance in cm to trigger obstacle avoidance
const long interval = 5000;       // Interval for LED state

unsigned long previousMillis = 0;
bool obstacleAvoidanceInProgress = false;
String command;

// Motor definitions
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Function prototypes
void executeCommand(String cmd);
void forward();
void lforward();
void backward();
void left();
void right();
void uright();
void Stop();
int getDistance();
void park();

void setup() {
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
}

void loop() {
  // Check for commands via serial input
  while (Serial.available()) {
    command = Serial.readString();
    command.toLowerCase(); // Make the command case-insensitive
    Serial.println("Received Command: " + command);
    if (!obstacleAvoidanceInProgress) {
      executeCommand(command);
    }
  }

  // Check distance from obstacle
  int distance = getDistance();
  unsigned long currentMillis = millis();

  // Obstacle avoidance logic
  if (distance <= distanceThreshold && !obstacleAvoidanceInProgress) {
    obstacleAvoidanceInProgress = true;
    Stop();
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, LOW);
    previousMillis = currentMillis;

    // Turn right to avoid obstacle
    uright();
    delay(1000); // Time to complete turn
    Stop(); // Stop after turning
    obstacleAvoidanceInProgress = false;
  } else {
    digitalWrite(RedLED, LOW);
    if (currentMillis - previousMillis < interval && !obstacleAvoidanceInProgress) {
      digitalWrite(GreenLED, HIGH);
    } else {
      digitalWrite(GreenLED, LOW);
    }
  }
}

void executeCommand(String cmd) {
  if (cmd == "*forward#" || cmd == "*slow move forward#") {
    forward();
  } else if (cmd == "*backward#") {
    backward();
  } else if (cmd == "*left#") {
    left();
  } else if (cmd == "*right#") {
    right();
  } else if (cmd == "*park#") {
    park();
  } else {
    Serial.println("Unknown command: " + cmd);
  }
}

void forward() {
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000); // Adjust as needed
  Stop();
}

void backward() {
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1000);
  Stop();
}

void left() {
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor3.setSpeed(turnSpeed);
  motor4.setSpeed(turnSpeed);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(500);
  Stop();
}

void right() {
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor3.setSpeed(turnSpeed);
  motor4.setSpeed(turnSpeed);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(500);
  Stop();
}

void uright() {
  right(); // Simplified to reuse right turn logic
}

void park() {
  backward();
  delay(500);
  left();
  delay(300);
  forward();
  delay(500);
  Stop();
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(1);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  int duration = pulseIn(Echo, HIGH);
  int distance = duration * 0.034 / 2; // Convert duration to distance (cm)
  return distance;
}

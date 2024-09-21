# Obstacle Avoidance Robot with AFMotor Library

This project controls a robotic vehicle equipped with four DC motors, ultrasonic sensors, and LEDs for obstacle detection and avoidance. The robot can move forward, backward, left, and right, and automatically avoids obstacles by using an ultrasonic sensor to measure distance. When an obstacle is detected, the robot performs a right turn to avoid it. The system also provides feedback through LEDs, indicating whether the robot has detected an obstacle.

## Features

- **Obstacle Detection**: The ultrasonic sensor measures the distance to objects, triggering obstacle avoidance if they are too close.
- **Motor Control**: Four DC motors (front-left, front-right, rear-left, rear-right) allow the robot to move in all directions (forward, backward, left, right).
- **Obstacle Avoidance**: When an obstacle is detected, the robot stops and makes a right turn to avoid the obstacle.
- **LED Feedback**: 
  - Red LED: Indicates the presence of an obstacle.
  - Green LED: Blinks when no obstacle is detected.

## Components

- 4 x DC Motors
- 1 x Ultrasonic Sensor (HC-SR04)
- 1 x Red LED
- 1 x Green LED
- 1 x Arduino (or compatible microcontroller)
- Motor Driver Shield (using AFMotor library)

## Pin Configuration

- **Echo Pin**: A0 (Ultrasonic sensor echo pin)
- **Trig Pin**: A1 (Ultrasonic sensor trigger pin)
- **Red LED Pin**: 8
- **Green LED Pin**: 7

## Software Requirements

- **Arduino IDE**: To upload the code to the microcontroller.
- **AFMotor Library**: For controlling the motors. You can install the AFMotor library through the Arduino IDE Library Manager.

## How It Works

1. **Obstacle Detection**: The robot continuously checks the distance using the ultrasonic sensor.
   - If the distance is less than 20 cm, the robot stops and the Red LED turns on.
   - The robot then makes a right turn for 1 second to avoid the obstacle.
   - After turning, the robot stops, the Red LED turns off, and it continues checking for obstacles.
   
2. **LED Feedback**: 
   - The Red LED indicates that an obstacle is detected and the robot is avoiding it.
   - The Green LED blinks in regular intervals when no obstacle is present.

3. **Command Execution**: The robot also accepts commands via serial to manually control its movement:
   - `*forward#`: Move forward.
   - `*backward#`: Move backward.
   - `*left#`: Turn left.
   - `*right#`: Turn right.
   - `*park#`: Execute a parking maneuver.

## How to Use

1. **Upload the code**: Use the Arduino IDE to upload the provided `.ino` sketch to the microcontroller.
2. **Connect the components**: Follow the pin configuration section to connect the ultrasonic sensor, LEDs, and motors to the Arduino.
3. **Power the robot**: Provide power to the Arduino and the motor driver.
4. **Run the robot**: The robot will automatically avoid obstacles. You can also control it using serial commands via the Serial Monitor in the Arduino IDE.

## Commands

Commands can be sent to the robot via the Arduino's Serial Monitor (set to 9600 baud):
- `*forward#`: Move the robot forward.
- `*backward#`: Move the robot backward.
- `*left#`: Turn the robot left.
- `*right#`: Turn the robot right.
- `*park#`: Perform a parking sequence.

## Author

This project was developed as part of a robotic control system utilizing obstacle detection and motor control with the AFMotor library.

---

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Initialize the PWM driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150 // Minimum pulse length count (out of 4096)
#define SERVOMAX 600 // Maximum pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Control via Serial Input");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000); // Set the oscillator frequency
  pwm.setPWMFreq(SERVO_FREQ); // Set the PWM frequency to 50 Hz

  delay(10);
}

// Function to map angles to PWM pulse values
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the input from Serial Monitor
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove extra whitespace or newline characters

    if (input.length() > 0) {
      // Parse the input into servo number and angle
      int separatorIndex = input.indexOf(',');
      if (separatorIndex != -1) {
        int servoNum = input.substring(0, separatorIndex).toInt();
        int angle = input.substring(separatorIndex + 1).toInt();

        // Validate input values
        if (servoNum >= 0 && servoNum < 16 && angle >= 0 && angle <= 180) {
          int pulse = angleToPulse(angle);
          pwm.setPWM(servoNum, 0, pulse);
          Serial.print("Servo ");
          Serial.print(servoNum);
          Serial.print(" set to angle ");
          Serial.println(angle);
        } else {
          Serial.println("Invalid input! Use: servoNum,angle (e.g., 2,90)");
        }
      } else {
        Serial.println("Invalid format! Use: servoNum,angle (e.g., 2,90)");
      }
    }
  }
}

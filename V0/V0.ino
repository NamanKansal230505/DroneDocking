#include <ESP32Servo.h>

// Create a servo object
Servo myServo;

// Define the GPIO pin the servo's signal wire is connected to
const int servoPin = 1;

void setup() {
  // Attach the servo on the defined pin to the servo object
  myServo.attach(servoPin);
  
  // Optional: Print a message to the Serial Monitor
  Serial.begin(115200);
  Serial.println("Servo control example");
}

void loop() {
  // Move the servo to the 90-degree position (clockwise)
  myServo.write(90);
  Serial.println("Moved to 90 degrees");
  delay(2000); // Wait for 2 seconds

  // Move the servo back to the 0-degree position (counter-clockwise)
  myServo.write(0);
  Serial.println("Moved back to 0 degrees");
  delay(2000); // Wait for 2 seconds
}

//test code only to verify Servo motor is working. 

#include "Servo.h"

Servo myServo;

void setup() {
    Serial.begin(9600);
    myServo.attach(1); // Attach the servo to pin 1 (TX)
}

void loop() {
    if (Serial.available() > 0) {
        int angle = Serial.parseInt(); // Read the angle from the serial monitor
        if (angle >= 0 && angle <= 180) {
            myServo.write(angle); // Set the servo to the specified angle
            Serial.print("Servo angle set to: ");
            Serial.println(angle);
        } else {
            Serial.println("Invalid angle. Please enter a value between 0 and 180.");
        }
    }
}
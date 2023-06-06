#include <AccelStepper.h>
#define encoderPinA 2
#define encoderPinB 3
#define motorStepPin 8
#define motorDirPin 9

Encoder encoder(encoderPinA, encoderPinB);
AccelStepper stepper(1, motorStepPin, motorDirPin);
const int targetPosition = 1000;  -
boolean isMoving = true;
void setup() {
  Serial.begin(9600);
  encoder.write(0);
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
}
void loop() {
  int encoderPosition = encoder.read();
  Serial.print("Encoder Konumu: ");
  Serial.println(encoderPosition);

  if (isMoving) {
    if (encoderPosition < targetPosition) {
      stepper.setSpeed(1000);
      stepper.runSpeed();
    } else {
      isMoving = false;
      stepper.stop();
      Serial.println("Motor durdu.");
    }
  }

  delay(100);
}

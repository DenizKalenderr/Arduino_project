#include <AccelStepper.h>
#define encoderPinA 2
#define encoderPinB 3

#define motorStepPin 8
#define motorDirPin 9

// Encoder nesnesi 
Encoder encoder(encoderPinA, encoderPinB);
AccelStepper stepper(1, motorStepPin, motorDirPin); // 1 motor sürücü ile çalışacağımızı belirtiyoruz

void setup() {
  Serial.begin(9600);
  encoder.write(0); // Encoder konumunu sıfırlama
  // Motor ayarları
  stepper.setMaxSpeed(1000); 
  stepper.setAcceleration(500); 
}
void loop() {
  int encoderPosition = encoder.read();
  Serial.print("Encoder Konumu: ");
  Serial.println(encoderPosition);
  
  // Motor hareketini ayarlama
  if (encoderPosition < 100) {
    stepper.setSpeed(100); 
  } else if (encoderPosition > 200) {
    stepper.setSpeed(-100); 
  } else {
    stepper.setSpeed(0); 
  }
  // Motoru belirlenen hız ve yönle hareket ettirme
  stepper.runSpeed();
}

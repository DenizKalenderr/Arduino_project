const int stepPin = 2;
const int dirPin = 3;

void setup() {
  
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  
  int speed = getUserSpeed();
  // Adım motoru hızını ayarla
  setMotorSpeed(speed);
  // Adım motorunu döndür
  stepMotor();
}

// Kullanıcının hız değerini al
int getUserSpeed() {
  Serial.println("Hiz degerini giriniz (0-255):");
  while (!Serial.available()) {
  }
  int speed = Serial.parseInt();
  Serial.print("Hiz: ");
  Serial.println(speed);
  return speed;
}

void setMotorSpeed(int speed) {
  int delayTime = map(speed, 0, 255, 1000, 1); // Hız değerini delay süresine dönüştür
  Serial.print("Delay Suresi: ");
  Serial.println(delayTime);
  digitalWrite(dirPin, HIGH); 
  delay(50);
  digitalWrite(dirPin, LOW);
  delay(50);
  digitalWrite(stepPin, LOW); // Başlangıç ​​pozisyonunda sıfırla
  delay(50);
}

void stepMotor() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(500);
}

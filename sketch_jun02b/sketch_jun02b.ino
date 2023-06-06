const int STEP_PIN = 2;
const int DIR_PIN = 3;
const int ENABLE_PIN = 4;

int stepsPerRevolution = 200;
float stepDelay = 0;
int numberOfSteps = stepsPerRevolution * 1.5;
int direction = 1;
float stepsPerSecond = 50.0;

void setup() {
  
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);
  
  Serial.begin(9600); 
}
void loop() {
  // Yönü ayarla (1 veya 0)
  digitalWrite(DIR_PIN, direction);
  stepDelay = (1000.0 / stepsPerSecond) / stepsPerRevolution;

  for(int i=0; i < numberOfSteps; i++) {
    
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);
    delay(stepDelay);
    
  }

  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    
    switch (incomingByte) {
      case 'f': // ileri yönde hareket
        direction = 1;
        break;
        
      case 'r': // ters yönde hareket
        direction = 0;
        break;
        
      case 's': // durma
        stepsPerSecond = 0;
        break;
        
      default: // hızı ayarla
        stepsPerSecond = (float) (incomingByte - '0');
        break;
    }
  }
}

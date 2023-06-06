const int bufferSize = 700;
int buffer[bufferSize];
volatile int head = 0;

void setup() {
  Serial.begin(115200);
  // Configure Timer1 to generate interrupt at 1000 Hz
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 520; // 16 MHz clock, prescaler = 1024, OCR1A = (16000000 / (1024 * 1000)) - 1 //hertz e çevirerek yaptım.
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | ( 1<< CS10); 
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}
void loop() {
  // Main loop
  if (Serial.available()) {
    Serial.read();
    for (int i = 0; i < head; i++) {
      Serial.println(buffer[i]);
    }
  }
  //OCR1A değerleriyle oynasam da veri gönderemediğim için kodu optimize etmeye kadar verdim. Öncelikle SPI iletişimini, write ve read fonksiyonlarını kaldırdım. Prescaler değerini CS12 ve CS10 değerlerini kullanarak 1024 yaptım ve bu durumda OCR1A değeri de 520 oldu. Kodu bu şekilde düzenledikten sonra herhangi bir hata almadan çalıştı.


}
ISR(TIMER1_COMPA_vect) {
  // Interrupt service routine
  int data = analogRead(A0);
  buffer[head++] = data;
  if (head == bufferSize) {
    head = 0;
  }
}

#include <SPI.h>
const int bufferSize = 200;
int buffer[bufferSize];
volatile int head = 0;
volatile int tail = 0;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  writeSRAM(0x0000, 0x000, buffer);

  noInterrupts();
  // Configure Timer1 to generate interrupt at 1 kHz
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A =1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |=  (1 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

void loop() {
  // Main loop
  if (Serial.available()) {
    Serial.read();
    for(int i = tail; i!=head; i =(i+1)%bufferSize){
      Serial.println(buffer[i]);      
      }
      readSRAM(0x000, bufferSize * sizeof(int), buffer);
  }
}
ISR(TIMER1_COMPA_vect) {
  // Interrupt service routine
  int data=1;
  buffer[head] = data;
  head = (head + 1) % bufferSize;
  if (head == tail) {
    tail = (tail + 1) % bufferSize;
  }
  if(head==0){
    writeSRAM(0x000, bufferSize * sizeof(int), buffer);    
    }
}
void writeSRAM(unsigned int address, unsigned int count, int *data){
  SPI.transfer(0x02);
  SPI.transfer(address >> 8);
  SPI.transfer(address & 0xFF);
  for(unsigned int i =0; i<count; i++){
    SPI.transfer(data[i] >> 8);
    SPI.transfer(data[i] >> 0xFF);    
    }  
  }
  void readSRAM(unsigned int address, unsigned int count, int *data){
    SPI.transfer(0x03);
    SPI.transfer(address >> 8);
    SPI.transfer(address & 0xFF);

    for(unsigned int i =0; i<count; i++){
      int highByte = SPI.transfer(0x00);
      int lowByte = SPI.transfer(0x00);
      data[i] = (highByte << 8) | lowByte;      
      }
    }

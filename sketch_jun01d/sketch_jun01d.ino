//slave
#include <Wire.h> 

int const pot_pin = A0;

char receivedData = "";

void setup (void)
{  
  Wire.begin(8);
  Wire.setClock(600000);
  Wire.onReceive(receiveData);
  Wire.onRequest(requestData);
  pinMode(pot_pin, INPUT);
  Serial.begin (9600);  
}   
void loop (void)
{  
}
void receiveData(){
  while(Wire.available()){
     receivedData = Wire.read();
     Wire.write(receivedData);
     Serial.print(receivedData);    
  }
}
void requestData(){
  Wire.write(analogRead(pot_pin));
 
  }

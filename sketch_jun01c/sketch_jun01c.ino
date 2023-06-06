//Master
#include <Wire.h>
void sendValue () {

      Wire.beginTransmission(8);
      Wire.write("PotValue");
      Wire.endTransmission();
      Serial.println("PotValue");
      delayMicroseconds(1000);
      Wire.requestFrom(8,1);

      while(Wire.available()){
        int receivedData = Wire.read();
        Serial.print(receivedData);
        }     
      }  
 
  void setup ()
  {
    Wire.begin();
    Wire.setClock(600000);
    Serial.begin(9600); 
  }  
  void loop (void)
  {
   while(Serial.available()> 0){
      char value = Serial.read();
      Serial.print(value);
      
      if(value == '1'){sendValue();}
      
      delayMicroseconds(1000);
   }
  } 

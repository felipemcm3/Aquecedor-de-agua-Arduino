#include <OneWire.h>
#include <DallasTemperature.h>
float temax; 
float temin;
OneWire pino(3);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
void setup(void)
{
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  barramento.begin();
  barramento.getAddress(sensor, 0); 
}
void loop()
{
  if(Serial.available()>1 ){
    int controle = Serial.parseFloat();
    if(controle == 0){
      temax = Serial.parseFloat();
    }
    if(controle == 1){
      temin = Serial.parseFloat();
    }
  }
  barramento.requestTemperatures(); 
  float temperatura = barramento.getTempC(sensor);
  Serial.println(temperatura);
  delay(500);
  if(temperatura <= temin){
    digitalWrite(6, LOW);
    
  }
  else if(temperatura >= temax){
    digitalWrite(6, HIGH);
    
  }
}

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

/*
  Temp sensor is on D8
  Heater relay on D2
  Cooler relay on D4
  Pump relay on D6  
 
*/
 
 float Celcius=0;
 float Fahrenheit=0;
 bool heater=false;
 bool pump=false;
 bool cooler=false;
 
void setup(void)
{
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  Serial.begin(9600);
  sensors.begin();
}

void loop(void)
{ 
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  
  // If the temp is low
  while (Celcius <= 4)
  {
      // Turn on Heater
      heater=true;
      // Turn on Pump
      pump=true;
  }
  
  // If the temp is high
  
  while (Celcius >= 22)
  {
      // Turn on cooler
      cooler=true;
      
      // Turn on pump
      pump=true;
  }
  
  if (heater == true)
  { digitalWrite(2, HIGH); }
  else
  { digitalWrite(2, LOW); }
  
  if (cooler == true)
  { digitalWrite(4, HIGH); }
  else
  { digitalWrite(4, LOW); }
  
  if (pump == true)
  { digitalWrite(6, HIGH); }
  else
  { digitalWrite(6, LOW); }
  
  delay(10000);
}

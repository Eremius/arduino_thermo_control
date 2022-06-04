#include <OneWire.h>
#include <DallasTemperature.h>
#include <Smoothed.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Smoothed <float> mySensor;

// Global Variables
bool heater = false;
bool pump = false;
bool cooler = false;

const int PumpPin = 5;
const int CoolerPin = 2;
const int HeaterPin = 3;
const int RunningPin = 6;

void setup(void)
{
  pinMode(PumpPin, OUTPUT);
  pinMode(CoolerPin, OUTPUT);
  pinMode(HeaterPin, OUTPUT);
  digitalWrite(PumpPin, LOW);
  digitalWrite(CoolerPin, LOW);
  digitalWrite(HeaterPin, LOW);
  Serial.begin(9600);
  mySensor.begin(SMOOTHED_AVERAGE, 150);
  mySensor.clear();
}


void loop(void)
{ 
  // BEGINNING OF LOGIC STAGE
  sensors.requestTemperatures(); 
  mySensor.add(sensors.getTempFByIndex(0));

  Serial.print("Temp: ");
  Serial.print(mySensor.get());
  Serial.print("\n");
  
  // If the temp is low
  if (mySensor.get() <= 55)
  {
      //Serial.print("Temp is LOW\n");
      heater = true;
      pump = true;
      cooler = false;
  } 
  else if (mySensor.get() > 55 && mySensor.get() < 80)
  {
    heater = false;
    cooler = false;
    pump = false;
  }
  else if (mySensor.get() >= 80)
  {
    //Serial.print("Temp is HIGH\n");
    cooler = true;
    pump = true;
    heater = false;
  }
  else
  {
    Serial.print("Temp Reading Error\n");
  }

  if (digitalRead(RunningPin) == HIGH)
  {
    Serial.print("RunningPin is HIGH\n");
    pump = true;
  }
  else { Serial.print("RunningPin is LOW\n"); }

// END OF LOGIC STAGE


// BEGINNING OF CONTROL STAGE
  if (heater == true)
  {
    // Turn Heater ON if OFF
    if (digitalRead(HeaterPin) == LOW )
    {
      digitalWrite(HeaterPin, HIGH);
      Serial.print("Heater ON\n");
    }
  }
  else if (heater == false)
  {
    if (digitalRead(HeaterPin) == HIGH )
    {
      digitalWrite(HeaterPin, LOW); 
      Serial.print("Heater OFF\n");
    }
  }

  if (pump == true)
  {
    if (digitalRead(PumpPin) == LOW )
      {
        digitalWrite(PumpPin, HIGH); 
        Serial.print("Pump ON\n");
      }
  }
  else if (pump == false)
  {
    if (digitalRead(PumpPin) == HIGH )
      {
        digitalWrite(PumpPin, LOW); 
        Serial.print("Pump OFF\n");
      }
  }

  if (cooler == true)
  {
    if (digitalRead(CoolerPin) == LOW )
      {
        digitalWrite(CoolerPin, HIGH); 
        Serial.print("Cooler ON\n");
      }
  }
  else if (cooler == false)
  {
    if (digitalRead(CoolerPin) == HIGH )
    {
      digitalWrite(CoolerPin, LOW); 
      Serial.print("Cooler OFF\n");
    }
  }

  // END OF CONTROL STAGE
  
  delay(1000);
}

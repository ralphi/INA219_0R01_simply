#include <Wire.h>
#include <INA219_10A.h>

#define ADD_INA 0x40  // Add_pads default

INA219_10A ina219 (ADD_INA);

void setup ( void ) {
  Serial.begin ( 9600 );
  while (!Serial);

  ina219.begin();
  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop ( void ) {
  Serial.print("I: " + String (ina219.getCurrent_A()) + " A");
  Serial.print("U: " + String (ina219.getBusVoltage_V()) + " V");
  Serial.print("P: " + String (ina219.getPower_W()) + " W");
  delay(1000);
}


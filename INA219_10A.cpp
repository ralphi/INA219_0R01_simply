/**************************************************************************/
/*! 
    @file     INA219_10A.cpp
    @author   Alex from Ergolding, simplified version 
	@license  BSD (see license.txt)
	Thanks to : K.Townsend (Adafruit Industries) - good documentation
	
	Driver for the INA219 current sensor whith 0.01 Ohms
	
	Adafruit invests time and resources providing the "default version" open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

    v1.001
*/
/**************************************************************************/

 #include "Arduino.h"
 #include <Wire.h>
 #include "INA219_10A.h"

/**************************************************************************/
INA219_10A::INA219_10A(uint8_t addr) {
  ina219_i2caddr = addr;
}

// begin ********************
void INA219_10A::begin(void) {
  Wire.begin();    
  setCalibration_16V_10A();
}

// I2C comunication ***** WRITE ***********
void INA219_10A::wireWriteRegister (uint8_t reg, int16_t value){
  Wire.beginTransmission(ina219_i2caddr);
    Wire.write(reg);                       // Register
    Wire.write((value >> 8) & 0xFF);       // Upper 8-bits
    Wire.write(value & 0xFF);              // Lower 8-bits
  Wire.endTransmission();
}

// I2C comunication ***** READ ***********
int16_t INA219_10A::wireReadRegister(uint8_t reg) {
  Wire.beginTransmission(ina219_i2caddr);
  Wire.write(reg);                       // Register
  Wire.endTransmission();
  delay(100); // Max 12-bit conversion time is 70msec per sample
  Wire.requestFrom(ina219_i2caddr, (uint8_t)2); 
  return ((Wire.read() << 8) | Wire.read());
}

// config 16V 10A  ***********
void INA219_10A::setCalibration_16V_10A(void) {
	
  ina219_currentDivider_mA = 1;	// 10A 0.01 Ohm
  ina219_currentDivider_A = 1000;	// 10A 0.01 Ohm
  ina219_powerMulti_mW = 20; // 10A 0.01 Ohm
  wireWriteRegister(INA219_REG_CALIBRATION, INA219_CALIBRATION_VALUE);

  uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
                    INA219_CONFIG_GAIN_4_160MV |
                    INA219_CONFIG_BADCRES_12BIT_128S_68MS |
					INA219_CONFIG_SADCRES_12BIT_128S_68MS |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
					
	wireWriteRegister(INA219_REG_CONFIG, config);

}
// ********** convert ShuntVoltage 
float INA219_10A::getShuntVoltage_mV() {
  int16_t value = wireReadRegister(INA219_REG_SHUNTVOLTAGE);
  return value * 0.01;
}

// ********** convert BusVoltage 
float INA219_10A::getBusVoltage_V() {
  int16_t value = wireReadRegister(INA219_REG_BUSVOLTAGE);
  // Shift to the right 3 to drop CNVR and OVF and multiply by LSB 4mV
  return (float)((value >> 3) * 0.004) ;
}

// ********** convert power Watt
float INA219_10A::getPower_mW() {
  int16_t value = wireReadRegister(INA219_REG_POWER);
  value *= ina219_powerMulti_mW;
  return (float) value;
}
float INA219_10A::getPower_W() {
  return (float) getPower_mW() * 0.001;
}

// ********** convert Current_mA
float INA219_10A::getCurrent_mA() {
  wireWriteRegister(INA219_REG_CALIBRATION, INA219_CALIBRATION_VALUE);
  int16_t value = wireReadRegister(INA219_REG_CURRENT);
  return (float)value;
}
// ********** convert Current_A
float INA219_10A::getCurrent_A() {
  return  (float)getCurrent_mA() * 0.001;
}
 
// **************************************************************************/

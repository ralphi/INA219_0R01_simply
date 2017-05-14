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

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define INA219_READ                            (0x01)
/*=========================================================================*/

/*=========================================================================
    CONFIG REGISTER (R/W)
    -----------------------------------------------------------------------*/
    #define INA219_REG_CONFIG                      (0x00)
    /*---------------------------------------------------------------------*/
    #define INA219_CONFIG_RESET                    (0x8000)  // Reset Bit

    #define INA219_CONFIG_BVOLTAGERANGE_16V        (0x0000)  // 0-16V Range
    #define INA219_CONFIG_GAIN_4_160MV             (0x1000)  // Gain 4, 160mV Range
    #define INA219_CONFIG_BADCRES_12BIT_128S_68MS  (0x0400)  // 12-bit bus res = 0..4097
    #define INA219_CONFIG_SADCRES_12BIT_128S_68MS  (0x0078)  // 128 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS (0x0007)	
/*=========================================================================*/

/*=========================================================================
    SHUNT VOLTAGE REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_SHUNTVOLTAGE                (0x01)
/*=========================================================================*/

/*=========================================================================
    BUS VOLTAGE REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_BUSVOLTAGE                  (0x02)
/*=========================================================================*/

/*=========================================================================
    POWER REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_POWER                       (0x03)
/*=========================================================================*/

/*=========================================================================
    CURRENT REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_CURRENT                     (0x04)
/*=========================================================================*/

/*=========================================================================
    CALIBRATION REGISTER (R/W)
    -----------------------------------------------------------------------*/
    #define INA219_REG_CALIBRATION                 (0x05)
	#define INA219_CALIBRATION_VALUE           	   (0x1000) 
	// cal = 0.04096 / (Current_LSB ´ RSHUNT)
	// Current LSB = 1mV ca. 30A
/*=========================================================================*/

class INA219_10A{
 public:
  INA219_10A(uint8_t addr);	// find out I2C add - default without change A0 A1 = 0x40
  void begin(void);

  float getBusVoltage_V(void);
  float getShuntVoltage_mV(void);
  float getCurrent_mA(void);
  float getCurrent_A(void);
  float getPower_W(void);
  float getPower_mW(void);

 private:
	// RSHUNT = 0.01               (Resistor value in ohms)
  uint8_t ina219_i2caddr;

  uint32_t ina219_currentDivider_mA;
  uint32_t ina219_currentDivider_A;
  uint32_t ina219_powerMulti_mW;
  
  void setCalibration_16V_10A(void);	// the only in this library
  void wireWriteRegister(uint8_t reg, int16_t value);
  int16_t wireReadRegister(uint8_t reg);

};

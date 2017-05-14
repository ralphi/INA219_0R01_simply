# INA219_0R01_simply
Modified Adafruit library for 0.01 ohms shunt and 16V

To use the library, you must replace the default shunt resistor 0.1 Ohm with 0.01 Ohm (min 1/4 W).  
The library does not provide any settings.   
It is fixed on:   
- Shunt: 0.01 ohms 
- optimum voltage: 16V 
- ADC Resolution: 12 bit (most accurate) 
- ADC Averaging: 68.10 ms (most accurate) 
  
Simple:  
  #define ADD_INA 0x40 // default      
  INA219_10A ina219 (ADD_INA);      
  ina219.begin ();      
  
The following commands are possible:       
  float getBusVoltage_V(void);  
  float getShuntVoltage_mV(void);  
  float getCurrent_mA(void);  
  float getCurrent_A(void);  
  float getPower_W(void);  
  float getPower_mW(void);  
  
  Only tested with ESP8266 ESP-12  
  - SDA -> GPIO 4
  - SCL -> GPIO 5

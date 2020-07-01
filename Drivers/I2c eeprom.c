#include "I2c eeprom.h"

void EEPROM_Write(unsigned int add, unsigned char data)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2c_WriteSlaveAddress(EEPROM_Address_W))
  I2C_Master_RepeatedStart();
  I2C_Master_Write(add);
  I2C_Master_Write(data);
  I2C_Master_Stop();
}
// EEPROM Write Page
void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  for(unsigned int i=0; i<len; i++)
    I2C_Master_Write(data[i]);
  I2C_Master_Stop();
}

//-----------------------------
//-----[ Read Operations ]-----
//---[ Byte Read ]---
unsigned char EEPROM_Read(unsigned int add)
{
  unsigned char Data;
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
 // I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(EEPROM_Address_R);
  Data = I2C_Read_Byte();
  I2C_NACK();
  I2C_Master_Stop();
  return Data;
}
//---[ Sequential Read ]---
void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(EEPROM_Address_R);
  for(unsigned int i=0; i<len; i++)
  {
    data[i] = I2C_Read_Byte();
    I2C_ACK();
  }
  I2C_Master_Stop();
}
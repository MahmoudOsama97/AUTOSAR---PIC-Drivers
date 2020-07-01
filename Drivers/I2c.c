#include "I2c.h"

Port_ConfigType I2c_Configurations[2] =
{
    {PortC,PIN3,PORT_PIN_IN,HIGH,NO_PULL},
    {PortC,PIN4,PORT_PIN_IN,HIGH,NO_PULL}
};

void I2c_Init(I2c_ConfigType *Config_Ptr)
{
    if(Config_Ptr->I2c_Module == I2C0 && 
        Config_Ptr->I2c_Channel == 0 )
    {
        Port_Init(&I2c_Configurations[0]);
        Port_Init(&I2c_Configurations[1]);
    }
    else {/*error*/}
    CTL_REG1 |= 0x0F & Config_Ptr->I2c_Mode;
    SET_BIT(CTL_REG1,5);
    CTL_REG2 = 0;
    ADDR_REG = (_XTAL_FREQ/(4*Config_Ptr->I2c_Baudrate))-1;
    STAT_REG = 0;
    
    //Config_Ptr->I2c_Status = I2C_IDLE;   
}

void I2C_Master_Wait()
{
  while ((STAT_REG & 0x04) || (CTL_REG2 & 0x1F));
}
void I2C_Master_Start()
{
  I2C_Master_Wait();
  SET_BIT(CTL_REG2,SEN_BIT);
}
void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  SET_BIT(CTL_REG2,RSEN_BIT);
}
void I2C_Master_Stop()
{
  I2C_Master_Wait();
  SET_BIT(CTL_REG2,PEN_BIT);
}
unsigned char I2C_Master_Write(unsigned char data)
{
  I2C_Master_Wait();
  BUFF_REG = data;
  while(!BUSY_BIT); // Wait Until Completion
  BUSY_BIT = 0;
  return ACKSTAT;
}
unsigned char I2c_WriteSlaveAddress(unsigned char data)
{
  I2C_Master_Wait();
  BUFF_REG = data;
  while(!BUSY_BIT); // Wait Until Completion
  BUSY_BIT = 0;
  return ACKSTAT;
}

Std_ReturnType I2c_WriteIB(I2c_ChannelType Channel,
                    const I2c_DataBufferType* DataBufferPtr)
{
    if(Channel==0)
    {
        
    }
    else {/*error*/}
}

unsigned char I2C_Read_Byte(void)
{
  //---[ Receive & Return A Byte ]---
  I2C_Master_Wait();
  SET_BIT(CTL_REG2,RCEN_BIT); // Enable & Start Reception
  while(!BUSY_BIT); // Wait Until Completion
  BUSY_BIT = 0; // Clear The Interrupt Flag Bit
  I2C_Master_Wait();
  return BUFF_REG; // Return The Received Byte
}
void I2C_ACK(void)
{
  CLEAR_BIT(CTL_REG2,ACKDT_BIT);// 0 -> ACK
  I2C_Master_Wait();
  SET_BIT(CTL_REG2,ACKEN_BIT);// Send ACK
}
void I2C_NACK(void)
{
  SET_BIT(CTL_REG2,ACKDT_BIT); // 1 -> NACK
  I2C_Master_Wait();
  SET_BIT(CTL_REG2,ACKEN_BIT);ACKEN = 1; // Send NACK
}



//void I2C_Master_Init(const unsigned long baud)
//{
//  SSPCON = 0b00101000;
//  SSPCON2 = 0;
//  SSPADD = (_XTAL_FREQ/(4*baud))-1;
//  SSPSTAT = 0;
//  Port_Init(&I2c_Configurations[0]);
//  Port_Init(&I2c_Configurations[1]);
//  
//}
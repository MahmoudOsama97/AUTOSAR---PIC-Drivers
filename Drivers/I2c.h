 #include <xc.h>
#include "config.h"
#include "Port.h"
#define I2C_BaudRate 100000 // I2C Baud Rate = 100 Kbps
#define _XTAL_FREQ 4000000

#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0

#define CTL_REG1 SSPCON
#define CTL_REG2 SSPCON2
#define STAT_REG SSPSTAT
#define BUFF_REG SSPBUF
#define ADDR_REG SSPADD
#define BUSY_BIT SSPIF

enum{
    SEN_BIT,RSEN_BIT,PEN_BIT,RCEN_BIT,
    ACKEN_BIT,ACKDT_BIT,ACKSTAT_BIT
};

typedef uint16_t I2c_NumberOfDataType;
typedef uint8_t I2c_DataBufferType;
typedef uint16_t I2c_ChannelType;
typedef uint32_t I2c_BaudRateType;

typedef enum{
    I2C_SLAVE_7BIT =      0b0110,
    I2C_SLAVE_10BIT =     0b0111,
    I2C_MASTER =          0b1000,
    I2C_MASTER_FRIMWARE=  0b1001,
    I2C_SLAVE_7BIT_INT_EN=0b1010,
    I2C_SLAVE_10BIT_INT_EN=0b1011
}I2c_ModeType;

typedef enum{
    I2C0     //,I2C1  : NOT SUPPORTED BY HW
}I2c_ModuleType;

typedef enum{
    I2C_UNINIT,
    I2C_IDLE,
    I2C_BUSY
}I2c_StatusType;

typedef enum{
    INTERNAL_BUFFER  //EXTERNAL_BUFFER
}I2c_BufferSourceType;

typedef enum{
    MSB_FIRST,  //LSB_FIRST
}I2c_TransferStartType;
typedef enum{
    BITS_8   //,BITS_16,BITS_32  : NOT SUPPORTED BY HW
}I2c_DataWidthType;

typedef struct{
    I2c_ModuleType I2c_Module;
    I2c_ChannelType I2c_Channel;
    I2c_BaudRateType I2c_Baudrate;
    I2c_ModeType I2c_Mode;
    I2c_DataBufferType I2c_DefaultTransmitValue;
    I2c_DataWidthType I2c_DataWidth;
    I2c_BufferSourceType I2c_BufferSource;
    I2c_TransferStartType I2c_TransferStart;
    I2c_StatusType I2c_Status;
}I2c_ConfigType;




void I2c_Init(I2c_ConfigType *Config_Ptr);
Std_ReturnType I2c_WriteIB ( I2c_ChannelType Channel, const I2c_DataBufferType* DataBufferPtr );
Std_ReturnType I2c_ReadIB ( I2c_ChannelType Channel, const I2c_DataBufferType* DataBufferPtr );
I2c_StatusType I2c_GetStatus ( void );
void I2C_Master_DeInit();

void I2C_Master_Init(const unsigned long baud);
void I2C_Master_Wait();
void I2C_Master_Start();
unsigned char I2c_WriteSlaveAddress(unsigned char data);
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char);
unsigned char I2C_Read_Byte(void);
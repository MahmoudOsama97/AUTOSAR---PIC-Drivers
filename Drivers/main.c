//#include "7seg.h"
//#include "lcd.h"
//#include "I2c eeprom.h"
//void main()
//{
////  TRISA=0xC3;
////  TRISB=0x01;
////  TRISC=0x01;
////  TRISD=0x00;
////  TRISE=0x00;
//    LCD_init();
//    LCD_clearScreen();
//    LCD_displayString("Timer Settings");   
//    LCD_goToRowColumn(Second_ROW, First_Char);
//    LCD_displayString("HH:MM:SS");
//    while(1){}
////  lcd_init();
////  
////  TRISB=0x03;
////  lcd_cmd(L_CLR);
////  lcd_cmd(L_L1);
////  lcd_str("Ligue todos DIP");
////  lcd_cmd(L_L2);
////  lcd_str("Press. RB1");
////  while(PORTBbits.RB1);
////  
////    for(int i=0;i<4;i++)
////    {
////      switch(i)
////      {
////         case 0: 
////           PORTA=0x20;
////           break;
////         case 1: 
////           PORTA=0x10;
////           break;
////         case 2: 
////           PORTA=0x08;
////           break;
////         case 3: 
////           PORTA=0x04;
////           break;
////       }
////
////      for(int tmp=0;tmp<16;tmp++)
////      {
////        PORTD=display7s(tmp);	 
////        __delay_ms(200);	
////      }
////    }
//
//}


#include "I2c eeprom.h"

I2c_ConfigType x = {
    I2C0,0,100000,I2C_MASTER,
    0,BITS_8,INTERNAL_BUFFER,
    MSB_FIRST
};
//    I2c_ModuleType I2c_Module;
//    I2c_ChannelType I2c_Channel;
//    I2c_BaudRateType I2c_Baudrate;
//    I2c_ModeType I2c_Mode;
//    I2c_DataBufferType I2c_DefaultTransmitValue;
//    I2c_DataWidthType I2c_DataWidth;
//    I2c_BufferSourceType I2c_BufferSource;
//    I2c_TransferStartType I2c_TransferStart;
//    I2c_StatusType I2c_Status;
//};


void main(void) {
  //I2C_Master_Init(100000);
    I2c_Init(&x);
    unsigned int Address = 0x03f; // Some Random Address
  unsigned char Data = 0x22;     // Some Random Data To Write
  EEPROM_Write(Address, Data); // Write 0x04 @ 0x0020
  __delay_ms(10); // Wait tWR=10ms For Write To Complete
  TRISD = 0x00;
  PORTD = EEPROM_Read(Address); // Should Read 0x04
}


//#include "I2c eeprom.h"
//#include "adc.h"
//
//
////config
//
//void main(void) {
//    ADC_Init();
//    TRISD = 0x00;
//    TRISB = 0x00;
//    uint16_t x;
//  while(1)
//  {
//      x = ADC_Read(3);
//  PORTB = (uint8_t)x;
//  PORTD = (x>>8);
//  __delay_ms(10);
//  }
//}




//#define PORTA_PIN0    (ChannelId)1
//
//
//#include "Port.h"
//#include "Dio.h"
//#define _XTAL_FREQ 4000000
//#define PIC_MICRO_ACTIVE
//
//Port_ConfigType Port_Config[4] = {
//    {PortD,PIN0,PORT_PIN_OUT,HIGH,NO_PULL},
//    {PortD,PIN1,PORT_PIN_OUT,HIGH,NO_PULL},
//    {PortD,PIN2,PORT_PIN_OUT,HIGH,NO_PULL},
//    {PortB,PIN2,PORT_PIN_IN,LOW,PULL_UP}
//};
//
//void main(void) {
//  
//    Port_Init(&Port_Config[0]);
//    Port_Init(&Port_Config[1]);
//    Port_Init(&Port_Config[2]);
//
//    while(1)
//    {
//        if(Dio_ReadChannel(3))
//             Dio_WriteChannel(1,LOW);
//        else
//             Dio_WriteChannel(1,HIGH);
//    }
//}
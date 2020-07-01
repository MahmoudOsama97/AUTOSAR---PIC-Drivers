
/* MODULE      : LCD
 * file type   : C file
 * AUTHOR      : Mohamed Ashraf Ibrahim
 * Description : Source file supports both 4 and 8 data bus mode for LCD
 * Notes       : Please check your connections and if it is different,
 *               redefine ports to be fit your drive connection
 *
 */

                           /*********************************************
                                       H files Included
                           *********************************************/

#include "lcd.h"
#include "micro_config.h"



/*IMP.NOTE : 
 1)
 All the drivers in this project are written by me except two drivers :
 * 1) LCD driver 
 * 2) keypad driver 
 * 
 * I do some changes to them to be suitable for the project 
 * but I got them from Internet  
 * 
 * 
 * 
 2) For Keypad driver , for better design I had to use PORT and DIO
 * drivers to isolate the keypad driver from the microcontroller 
 */
 

              /*******************************************************************************
                *                      Functions Definitions                                  *
                   *******************************************************************************/


/***************************************************
 * Name: LCD_DATA  
 * Parameters (in):char Data 
 * Return value: void
 * Description: Send data to the LCD 
 * 
 *********************************************************/


void LCD_DATA(unsigned char Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0;
  if(Data & 2)
    D5 = 1;
  else
    D5 = 0;
  if(Data & 4)
    D6 = 1;
  else
    D6 = 0;
  if(Data & 8)
    D7 = 1;
  else
    D7 = 0;
}



/***************************************************
 * Name: LCD_init  
 * Parameters (in):void
 * Return value: void
 * Description: Initialize the LCD module 
 * Initialize directions of data and commands pins 
 * send commands to the LCD according to the datasheet
 * 
 *********************************************************/


void LCD_init(void)
{
 
  
    ADCON1=0x0f; 
    
  // IO Pin Configurations
  LCD_DATA_PORT_DIRECTION = 0x00;
  LCD_RS_DIRECTION = 0;
  LCD_EN_DIRECTION = 0; 
  // The Init. Procedure As Described In The Datasheet
  LCD_DATA(0x00);
  __delay_ms(30);
  __delay_us(LCD_EN_Delay);
  
  LCD_sendCommand(0x03);  
  __delay_ms(5);
  LCD_sendCommand(0x03);
  __delay_us(150);
  LCD_sendCommand(0x03);
  LCD_sendCommand(0x02);
  LCD_sendCommand(0x02);
  LCD_sendCommand(0x08);
  LCD_sendCommand(0x00);
  LCD_sendCommand(0x0C);
  LCD_sendCommand(0x00);
  LCD_sendCommand(0x06);
 

}


/***************************************************
 * Name: LCD_sendCommand  
 * Parameters (in):char command 
 * Return value: void
 * Description: Send command to the LCD 
 * 
 *********************************************************/


void LCD_sendCommand(uint8 command){
     // Select Command Register
  RS = 0;
  // Move The Command Data To LCD
  LCD_DATA(command);
  // Send The EN Clock Signal
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0; 
}


/***************************************************
 * Name: LCD_displayCharacter  
 * Parameters (in):char data 
 * Return value: void
 * Description: Display character to the LCD 
 * Note : 4-bit mode 
 * 
 *********************************************************/

void LCD_displayCharacter(uint8 data)
{
    char Low4,High4;
  Low4 = data & 0x0F;
  High4 = data & 0xF0;
  RS = 1;
  LCD_DATA(High4>>4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_DATA(Low4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}


/***************************************************
 * Name: LCD_displayString  
 * Parameters (in):string 
 * Return value: void
 * Description: Display string on the LCD 
  
 *********************************************************/

void LCD_displayString(const char *Str)
{
int i;
  for(i=0;Str[i]!='\0';i++)
    LCD_displayCharacter(Str[i]);
}


/***************************************************
 * Name: LCD_goToRowColumn  
 * Parameters (in): char row , char col
 * Return value: void
 * Description: Starting displaying according to the inputs
  
 *********************************************************/

void LCD_goToRowColumn(uint8 row,uint8 col)
{
  	unsigned char Temp,Low4,High4;
  if(row == 0) 
  {
    Temp = 0x80 + col; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_sendCommand(High4);
    LCD_sendCommand(Low4);
  }
  if(row == 1) 
  {
    Temp = 0xC0 + col;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_sendCommand(High4);
    LCD_sendCommand(Low4);
  }
    if(row == 2) 
  {
    Temp = 0x90 + col ;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_sendCommand(High4);
    LCD_sendCommand(Low4);
  }
     if(row == 3) 
  {
    Temp = 0xD0 + col ;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_sendCommand(High4);
    LCD_sendCommand(Low4);
  } 
}

/***************************************************
 * Name: LCD_intgerToString  
 * Parameters (in):int data 
 * Return value: void
 * Description: Display numbers on the LCD 
  
 *********************************************************/

void LCD_intgerToString(int data)
{
   int buff[16]; /* String to hold the ascii result */
   itoa(buff ,data,10); /* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
  LCD_sendCommand(0);
  LCD_sendCommand(1);
   LCD_goToRowColumn(0,0);
}



//#include "lcd.h"
//#define _XTAL_FREQ 4000000
//
//void lcd_wr(unsigned char val)
//{
//  LPORT=val;
//}
//
//void lcd_cmd(unsigned char val)
//{
//	LENA=1;
//        lcd_wr(val);
//        LDAT=0;
//        __delay_ms(3);
//        LENA=0;
//        __delay_ms(3);
//	LENA=1;
//}
// 
//void lcd_dat(unsigned char val)
//{
//	LENA=1;
//        lcd_wr(val);
//        LDAT=1;
//        __delay_ms(3);
//        LENA=0;
//        __delay_ms(3);
//	LENA=1;
//}
//
//void lcd_init(void)
//{
//	LENA=0;
//	LDAT=0;
//	__delay_ms(20);
//	LENA=1;
//	
//	lcd_cmd(L_CFG);
//	__delay_ms(5);
//	lcd_cmd(L_CFG);
//        __delay_ms(1);
//	lcd_cmd(L_CFG); //configura
//	lcd_cmd(L_OFF);
//	lcd_cmd(L_ON); //liga
//	lcd_cmd(L_CLR); //limpa
//	lcd_cmd(L_CFG); //configura
//    lcd_cmd(L_L1);
//}
//
//void lcd_str(const char* str)
//{
// unsigned char i=0;
//  
// while(str[i] != 0 )
// {
//   lcd_dat(str[i]);
//   i++;
// }  
//}
//
//

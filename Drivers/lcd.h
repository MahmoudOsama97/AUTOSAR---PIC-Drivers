


#ifndef _LCD_H_
#define _LCD_H_

/*********************************************
 *            H files Included               *
 *********************************************/


#include "std_types.h" 
#include "stdlib.h" 

/******************************************
 *           MACROS DEF                *
 ******************************************/
#define LCD_EN_Delay 500

#define LCD_DATA_PORT_DIRECTION TRISD
#define LCD_RS_DIRECTION TRISE2
#define LCD_EN_DIRECTION TRISE1
#define RS RE2
#define EN RE1
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

 

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);
void LCD_DATA(unsigned char Data) ;

/* LCD Parameters */
#define First_ROW 0
#define Second_ROW 1
#define Third_ROW 2
#define Fourth_ROW 3

#define First_Char 0
#define Second_Char 1
#define Third_Char 2
#define Fourth_Char 3
#define Fifth_Char 4
#define Sixth_Char 5
#define Seventh_Char 6
#define Eighth_Char 7
#define Ninth_Char 8
#define Tenth_Char 9



#endif /* LCD_H_ */



//#include <xc.h>
//
//#define LENA  PORTEbits.RE1
//#define LDAT  PORTEbits.RE2
//#define LPORT PORTD
//
//
//#define L_ON	0x0F
//#define L_OFF	0x08
//#define L_CLR	0x01
//#define L_L1	0x80
//#define L_L2	0xC0
//#define L_CR	0x0F		
//#define L_NCR	0x0C	
//
//#define L_CFG   0x38
//
//void lcd_init(void);
//void lcd_cmd(unsigned char val); 
//void lcd_dat(unsigned char val);
//void lcd_str(const char* str);
//

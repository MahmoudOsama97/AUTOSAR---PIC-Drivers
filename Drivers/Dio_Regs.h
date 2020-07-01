
#ifndef DIO_REGS_H
#define DIO_REGS_H

#include "std_types.h"

#define DDR_BASE    0x085
#define PORT_BASE   0x005
#define OPTION_REG  (*(volatile uint8 *)0x081)

/* Definition for PORTA Registers */
#define PORTA_REG	(*(volatile uint8 *)0x005)
#define DDRA_REG	(*(volatile uint8 *)0x085)
#define PINA_REG 	(*(volatile uint8 *)0x005)

/* Definition for PORTB Registers */
#define PORTB_REG	(*(volatile uint8 *)0x006)
#define DDRB_REG	(*(volatile uint8 *)0x086)
#define PINB_REG 	(*(volatile uint8 *)0x006)

/* Definition for PORTC Registers */
#define PORTC_REG	(*(volatile uint8 *)0x007)
#define DDRC_REG	(*(volatile uint8 *)0x087)
#define PINC_REG 	(*(volatile uint8 *)0x007)

/* Definition for PORTD Registers */
#define PORTD_REG	(*(volatile uint8 *)0x008)
#define DDRD_REG	(*(volatile uint8 *)0x088)
#define PIND_REG 	(*(volatile uint8 *)0x008)

/* Definition for PORTE Registers */
#define PORTE_REG	(*(volatile uint8 *)0x009)
#define DDRE_REG	(*(volatile uint8 *)0x089)
#define PINE_REG 	(*(volatile uint8 *)0x009)

#endif /* DIO_REGS_H */

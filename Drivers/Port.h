#ifndef PORT_H
#define PORT_H

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#define Pins_Total_Num 32
#define TOTAL_PORTS_NB 5

#define PORT_DIR_CHANGEABLE   STD_OFF
#define PORT_MODE_CHANGEABLE  STD_OFF
#define PORT_SET_PIN_DIRECTION_API  STD_OFF
#define PORT_SET_PIN_MODE_API  STD_OFF

#define HWREG(X,Y)				(*((volatile uint8*)(((uint8)X)+((uint8)Y))))
#define HWOR(X,Y)				(*((volatile uint8*)(((uint8)X)|((uint8)Y))))

typedef uint8 Port_PinType ;  //pin
typedef uint8 Port_PinModeType;  //

typedef enum {
	PORT_PIN_IN ,
	PORT_PIN_OUT
}Port_PinDirectionType;

typedef enum {
	PULL_UP ,
	PULL_DOWN,
    NO_PULL
}Port_PullConfig ;

typedef enum{
	NOT_CHANGEABLE,
    CHANGEABLE
}Port_PinChangeable;

typedef enum {
    PortA, 
    PortB,
    PortC,
    PortD,
    PortE
}Port_PortType;

typedef struct {
	Port_PinType port;
	Port_PinType pin_num;
    Port_PinDirectionType direction;
    Port_PullConfig pulling ;
}Port_ConfigTypeParam;

typedef enum {
    PORT_NOT_INITIALIZED,
    PORT_INITIALIZED  
}Port_PortStatus;

typedef struct {
    Port_PortType Port;
	Port_PinType Pin;
    Port_PinDirectionType PinDirection;
  //  Port_PinModeType PinMode;    NOT SUPPORTED BY HARDWARE
    uint8 PinIntitLevel;
    Port_PullConfig PullConfig;
#if (PORT_DIR_CHANGEABLE == STD_ON)
    Port_PinChangeable PinDirChangeable;
#endif
#if (PORT_MODE_CHANGEABLE == STD_ON)
    Port_PinChangeable PinModeChangeable;
#endif
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);


void SetPortDirection(Port_ConfigTypeParam * Config_Ptr) ;

#endif
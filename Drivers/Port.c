#include "Port.h"
#include "Dio_Regs.h"


//extern Port_ConfigType Port_Config[4];
//
//Port_ConfigType Port_Config[4] = {
//    {PortD,PIN0,PORT_PIN_OUT,HIGH,NO_PULL},
//    {PortD,PIN1,PORT_PIN_OUT,HIGH,NO_PULL},
//    {PortD,PIN2,PORT_PIN_OUT,HIGH,NO_PULL},
//    {PortB,PIN2,PORT_PIN_IN,LOW,PULL_UP}
//};

Port_PortStatus PortStatus[TOTAL_PORTS_NB]= {PORT_NOT_INITIALIZED,
PORT_NOT_INITIALIZED,PORT_NOT_INITIALIZED,PORT_NOT_INITIALIZED,PORT_NOT_INITIALIZED};

void Port_Init(const Port_ConfigType* ConfigPtr)
{
    volatile Port_PinType* Port_Dir_Ptr,*Port_Ptr = NULL;
    Port_Dir_Ptr = &HWREG(DDR_BASE, ConfigPtr->Port);
    Port_Ptr = &HWREG(PORT_BASE, ConfigPtr->Port);
    
    //set pin direction
    if (ConfigPtr->PinDirection == PORT_PIN_OUT) 
    {
        CLEAR_BIT(*Port_Dir_Ptr, ConfigPtr->Pin);
        //set pin initial level
        if (ConfigPtr->PinIntitLevel == HIGH) {
           SET_BIT(*Port_Ptr, ConfigPtr->Pin);
        } 
        else if (ConfigPtr->PinIntitLevel == LOW) {
           CLEAR_BIT(*Port_Ptr, ConfigPtr->Pin);
        }
    } 
    else if (ConfigPtr->PinDirection == PORT_PIN_IN) {
        SET_BIT(*Port_Dir_Ptr, ConfigPtr->Pin);
        //set pull up/down
        if (ConfigPtr->PullConfig == PULL_UP){
           CLEAR_BIT(OPTION_REG,7);
        }
        else if (ConfigPtr->PullConfig == PULL_DOWN){
           SET_BIT(OPTION_REG,7);
        }
    }
    #if (PORT_DIR_CHANGEABLE == STD_ON)
        //Not Supported by Hardware
    #endif
    #if (PORT_MODE_CHANGEABLE == STD_ON)
        //Not Supported by Hardware
    #endif
    //Port status
    PortStatus[ConfigPtr->Port]=PORT_INITIALIZED;
    
}

#if(PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction) {
	volatile Port_PinType* Port_Dir_Ptr = NULL;
    Port_PortType PortNb=Pin/8;
    Pin=Pin%8;
    Port_Dir_Ptr = &HWREG(DDR_BASE, PortNb);
    uint8 x ;
    for (int i = 0; i < 8; ++i) {
        if (Port_Config[i].Pin == Pin && Port_Config[i].Port == PortNb) 
                x = i;
    }
    if(Port_Config[x].PinDirChangeable == CHANGEABLE)
    {
        if(Direction == PORT_PIN_OUT)
        CLEAR_BIT(*Port_Dir_Ptr, Pin);
        else if (Direction == PORT_PIN_OUT)
        SET_BIT(*Port_Dir_Ptr, Pin);
    }
}
#endif

//void Port_RefreshPortDirection()
//{
//    volatile Port_PinType* Port_Dir_Ptr = NULL;
//    Port_ConfigType* Port_Config_this = NULL;
//  
//	for (int i = 0; i < 8; ++i) 
//    {
//        *Port_Config_this = Port_Config[i];
//        Port_Dir_Ptr = &Port_Config;
//        Port_Dir_Ptr = &HWREG(DDR_BASE, Port_Config_this->Port);
//		if (Port_Config->PinDirection == PORT_PIN_IN) 
//			CLEAR_BIT(*Port_Dir_Ptr, Port_Config_this->Pin);
//		 else if (Port_Config->PinDirection == PORT_PIN_OUT) 
//			SET_BIT(*Port_Dir_Ptr, Port_Config_this->Pin);
//    }
//}

#if(PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinModeType Mode) {
	volatile Port_PinType* Port_Mode_Ptr = NULL;
    Port_PortType PortNb=Pin/8;
    Pin=Pin%8;
    Port_Mode_Ptr = &HWREG(DDR_BASE, PortNb);
    uint8 x ;
    for (int i = 0; i < 8; ++i) {
        if (Port_Config[i].Pin == Pin && Port_Config[i].Port == PortNb) 
                x = i;
    }
    if(Port_Config[x].PinDirChangeable == CHANGEABLE)
    {
        if(Mode == DIO)
        CLEAR_BIT(*Port_Mode_Ptr, Pin);
        else if (Mode == I2C)
        SET_BIT(*Port_Mode_Ptr, Pin);
    }
}
#endif
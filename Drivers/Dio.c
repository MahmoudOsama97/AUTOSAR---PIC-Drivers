#include "Dio.h"
#include "Dio_Regs.h"
//Dio_ConfigChannelType x ={4,3};
//const Dio_ConfigType Dio_Configuration = {
//    DioConf_ON_LAMP_PORT_NUM, DioConf_ON_LAMP_CHANNEL_NUM,
//    DioConf_START_BUTTON_PORT_NUM, DioConf_START_BUTTON_CHANNEL_NUM,
//    DioConf_WEIGHT_SENSOR_PORT_NUM, DioConf_WEIGHT_SENSOR_CHANNEL_NUM,
//    DioConf_DOOR_SENSOR_PORT_NUM, DioConf_DOOR_SENSOR_CHANNEL_NUM,
//    DioConf_MOTOR_PORT_NUM, DioConf_MOTOR_CHANNEL_1_NUM,
//    DioConf_HEATER_PORT_NUM, DioConf_HEATER_CHANNEL_1_NUM,
//    DioConf_HEATER_LAMP_PORT_NUM, DioConf_HEATER_LAMP_CHANNEL_NUM,
//    DioConf_CANCEL_BUTTON_PORT_NUM, DioConf_CANCEL_BUTTON_CHANNEL_NUM,
//    DioConf_ON_BUTTON_PORT_NUM, DioConf_ON_BUTTON_CHANNEL_NUM
//};

Dio_ConfigGroupChannelType Dio_ConfigGroupChannel = 
{
    (Dio_PortType)3,  (Dio_ChannelType)1,
    (Dio_PortType)3,  (Dio_ChannelType)0,
    (Dio_PortType)3,  (Dio_ChannelType)2,
    (Dio_PortType)1,  (Dio_ChannelType)2
            
};

Dio_StateType Dio_Status = DIO_NOT_INITIALIZED;

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level) {
    volatile Dio_PortType * Port_Ptr = NULL;   
    Port_Ptr = &HWREG(PORT_BASE, Dio_ConfigGroupChannel.Channels[ChannelId].Port);
    if (Level == HIGH) 
        SET_BIT(*Port_Ptr, Dio_ConfigGroupChannel.Channels[ChannelId].Channel);
    else if (Level == LOW)
        CLEAR_BIT(*Port_Ptr, Dio_ConfigGroupChannel.Channels[ChannelId].Channel);
        
}

/************************************************************************************
 * Name: Dio_ReadChannel
 * Parameters (in): ChannelId - ID of DIO channel.
 * Return value: Dio_LevelType
 * Description: Function to return the value of the specified DIO channel.
 ************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId) {
    volatile Dio_PortType * Pin_Ptr = NULL;
    Dio_LevelType output = LOW;
    Pin_Ptr = &HWREG(PORT_BASE, Dio_ConfigGroupChannel.Channels[ChannelId].Port);
    if (BIT_IS_SET(*Pin_Ptr, Dio_ConfigGroupChannel.Channels[ChannelId].Channel)) 
        output = HIGH;
    else 
        output = LOW;
    return output;

}

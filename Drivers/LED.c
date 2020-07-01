#include "LED.h"
#include "Port.h"
#include "Dio.h" 

/*A structure to put all the configuration to be used 
 * by functions 
 */

static Port_ConfigTypeParam ON_Lamp_Config;
static Port_ConfigTypeParam Heater_Lamp_Config;

/***************************************************
 * Name: ledsConfigurations  (STATIC FUNCTION)
 * Parameters (in):void
 * Return value: void
 * Description:
 * 1) Leds Configurations : It makes define the port , pin , direction and pulling mode
 * for each pin 
 
 *********************************************************/


static void ledsConfigurations(void) {

	ON_Lamp_Config.port = DioConf_ON_LAMP_PORT_NUM;
	ON_Lamp_Config.pin_num = DioConf_ON_LAMP_CHANNEL_NUM;
	ON_Lamp_Config.direction = PORT_PIN_OUT;
	ON_Lamp_Config.pulling = PULL_DOWN;


	Heater_Lamp_Config.port = DioConf_HEATER_LAMP_PORT_NUM;
	Heater_Lamp_Config.pin_num = DioConf_HEATER_LAMP_CHANNEL_NUM;
	Heater_Lamp_Config.direction = PORT_PIN_OUT;
	Heater_Lamp_Config.pulling = PULL_DOWN;

}

/***************************************************
 * Name: ledsInit
 * Parameters (in):void
 * Return value: void
 * Description:
 * 1) Run the leds configuration function (Read its description)
 * 2) Set the directions of pins
 *********************************************************/

void ledsInit(void) {
	ledsConfigurations();
	SetPortDirection(&ON_Lamp_Config);

	SetPortDirection(&Heater_Lamp_Config);
}

/***************************************************
 * Name: writeLed
 * Parameters (in):Port_ConfigTypeParam * (pointer to structure), char Index ,char level 
 * Return value: void
 * Description: Takes pointer to structure and the DIO Index of one led and a level
 * to be assigned to be output level 
 * and return is the button is pressed / sensor is reading  or not 
 *********************************************************/

static void writeLed(Port_ConfigTypeParam *Config_ptr,
		uint8 INDEX_ID , uint8 Level) {
uint8 state = Level ;
		if (state == HIGH) {

			if (Config_ptr->pulling == PULL_DOWN) {
				Dio_WriteChannel(INDEX_ID,HIGH);
			} else if (Config_ptr->pulling == PULL_DOWN) {
				Dio_WriteChannel(INDEX_ID,LOW);
			}
		}
	else if (state == LOW) {
			if (Config_ptr->pulling == PULL_DOWN) {
				Dio_WriteChannel(INDEX_ID,LOW);
			} else if (Config_ptr->pulling == PULL_DOWN) {
				Dio_WriteChannel(INDEX_ID,HIGH);
		}
	}

	else {
		/*NO CODE*/
	}

}

/***************************************************
 * Name: writeONLamp
 * Parameters (in):char 
 * Return value: void
 * Description: takes level to be assigned to the ON lamp
 *********************************************************/

void writeONLamp(uint8 LEVEL) {

	writeLed(&ON_Lamp_Config,
			DioConf_ON_LAMP_ID_INDEX , LEVEL) ;
}

/***************************************************
 * Name: writeHeaterLamp
 * Parameters (in):char 
 * Return value: void
 * Description: takes level to be assigned to the Heater lamp
 *********************************************************/

void writeHeaterLamp(uint8 LEVEL) {

	writeLed(&Heater_Lamp_Config,
			DioConf_HEATER_LAMP_ID_INDEX , LEVEL) ;
}


#include "Arduino.h"
#define STARTPIN	16 //START pin
#define DRDYPIN		5 //DRDY pin
#define RESETPIN	4 //RESET pin
#define CS_PIN		17 //SPI CS pin
#define PWDNPIN		2 //PWDN
#define LEDPIN 		25 //LED for simple debug
//#define USERSWITCH	RPI_BPLUS_GPIO_J8_15 //SW to connect to GND
#define CS_DELAY	1  //how many microseconds of delay


void cs_select(void);
void cs_deselect(void);
void adc_wreg(int rgstr, int val); //write register
void adc_send_command(int cmd); //send command
void adc_rreg(int rgstr); //read register

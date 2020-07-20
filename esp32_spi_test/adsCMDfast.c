#include "adsCMDfast.h"
#include "ads1298.h"
#include "Arduino.h"

//bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE); //do NOT set any /CS automatically - repeated - just in case
//bcm2835_gpio_fsel(CS_PIN, BCM2835_GPIO_FSEL_OUTP); //CS is an output
/*

void cs_select(void){					//CS low (remember about negative logic here)
	digitalWrite(CS_PIN,LOW);
}

void cs_deselect(void){				//CS high (negative logic here)
	digitalWrite(CS_PIN,HIGH);
}	


void adc_wreg(int rgstr, int val){
	//writes one (val) byte to rgstr registry
	cs_select();
	char tempspibuf[3] = {0,0,0};
	tempspibuf[0]=(WREG | rgstr);
	tempspibuf[1]=0;
	tempspibuf[2]=val;
	
	vspi->transfer(tempspibuf);//bcm2835_spi_transfern(tempspibuf, 3);
  vspi->transfer(3);
	delayMicroseconds(CS_DELAY);
	cs_deselect();
}
*/

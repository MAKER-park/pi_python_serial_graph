#include <SPI.h>
#include "ads1298.h"
#include "adsCMD.h"

/* 
 SCP1000 sensor attached to pins 23, 19,18,5,17,16,4,15:
 DRDY: pin 17
 CSB: pin 5
 MOSI: pin 23
 MISO: pin 19
 SCK: pin 18
 rst : pin 16
 pwdn : pin 15
 start : pin 4
*/

static const int spiClk = 1000000; // 1 MHz


int gMaxChan = 0; //maximum number of channels supported by ads129n = 4,6,8
int gIDval = 0; //Device ID : lower 5 bits of  ID Control Register 


//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;

void setup() {
  Serial.begin(115200);
  using namespace ADS1298;
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi = new SPIClass(VSPI);
  
  //clock miso mosi ss

  //initialise vspi with default pins
  //SCLK = 18, MISO = 19, MOSI = 23, SS = 5
  vspi->begin();
  //alternatively route through GPIO pins of your choice

  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
   pinMode(dataReadyPin, INPUT);
   pinMode(chipSelectPin, OUTPUT);

   delay(500); //wait for the ads129n to be ready - it can take a while to charge caps
   adc_send_command(SDATAC);
   delay(10);
   gIDval = adc_rreg(ID); //lower 5 bits of register 0 reveal chip type
  switch (gIDval & B00011111 ) { //least significant bits reports channels
          case  B10000: //16
            gMaxChan = 4; //ads1294
            break;
          case B10001: //17
            gMaxChan = 6; //ads1296
            break; 
          case B10010: //18
            gMaxChan = 8; //ads1298
            break;
          case B11110: //30
            gMaxChan = 8; //ads1299
            break;
          default: 
            gMaxChan = 0;
  }

}

// the loop function runs over and over again until power down or reset
void loop() {
  //use the SPI buses
  //vspiCommand(0x32);
  adc_send_command(0x32);
  delay(500);
  
  if (digitalRead(dataReadyPin) == HIGH) {
    Serial.print("Device Type (ID Control Register): ");
    Serial.println(adc_rreg(3));
    /*Serial.print(" Channels: ");
    Serial.println(gMaxChan);*/
    // convert the temperature to celsius and display it:
  }

}

void vspiCommand(int cmd) {
  //use it as you would the regular arduino SPI API
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelectPin, LOW); //pull SS slow to prep other end for transfer
  vspi->transfer(cmd); 
  delayMicroseconds(1); 
  digitalWrite(chipSelectPin, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
}

void adc_send_command(int cmd) //send command
{
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelectPin, LOW);
  vspi->transfer(cmd);
  delayMicroseconds(1);
  digitalWrite(chipSelectPin, HIGH);
  vspi->endTransaction();
}

void adc_wreg(int reg, int val) //write register
{
  //see pages 40,43 of datasheet - 
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelectPin, LOW);
  vspi->transfer(ADS1298::WREG | reg);
  vspi->transfer(0);  // number of registers to be read/written – 1
  vspi->transfer(val);
  delayMicroseconds(1);
  digitalWrite(chipSelectPin, HIGH);
  vspi->endTransaction();
}

int adc_rreg(int reg){ //read register
  int out = 0;
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelectPin, LOW);
  vspi->transfer(ADS1298::RREG | reg);
  delayMicroseconds(5);
  vspi->transfer(0);  // number of registers to be read/written – 1
  delayMicroseconds(5);
  out = vspi->transfer(0);
    delayMicroseconds(1);
  digitalWrite(chipSelectPin, HIGH);
  vspi->endTransaction();
  return(out);
}

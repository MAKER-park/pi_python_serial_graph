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

static const int spiClk = 2000000; // 1 MHz


int gMaxChan = 0; //maximum number of channels supported by ads129n = 4,6,8
int gIDval = 0; //Device ID : lower 5 bits of  ID Control Register 
const int kPIN_LED = 25;


//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;

void setup() {
  Serial.begin(115200);
  using namespace ADS1298;
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi = new SPIClass(VSPI);

  vspi->begin();
  vspi->setBitOrder(MSBFIRST);
  vspi->setClockDivider(SPI_CLOCK_DIV4);
  vspi->setDataMode(SPI_MODE1);
  //alternatively route through GPIO pins of your choice

  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
   pinMode(dataReadyPin, INPUT);
   pinMode(chipSelectPin, OUTPUT);
   pinMode(IPIN_RESET, OUTPUT);//*optional
   pinMode(IPIN_PWDN, OUTPUT);//*optional
   pinMode(PIN_START, OUTPUT);

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

  while (Serial.read() >= 0) {} //http://forum.arduino.cc/index.php?topic=134847.0
  //while (!WiredSerial) ; //required by Leonardo http://arduino.cc/en/Serial/IfSerial (ads129n requires 3.3v signals, Leonardo is 5v)
  delay(200);  // Catch Due reset problem
  Serial.println("pinmode output");
  pinMode(kPIN_LED, OUTPUT); 

}

// the loop function runs over and over again until power down or reset
void loop() {
  
  //use the SPI buses
  //vspiCommand(0x32);
  adc_send_command(0x32);
  delay(500);
  
  if (digitalRead(dataReadyPin) == LOW) {
    Serial.print("Device Type (ID Control Register): ");
    Serial.println(gIDval);
    Serial.print(" Channels: ");
    Serial.println(gMaxChan);
  }
    // convert the temperature to celsius and display it:

    /*Serial.print("Device Type (ID Control Register): "); Serial.print(gIDval); Serial.print(" Channels: "); Serial.println(gMaxChan);
  digitalWrite(kPIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  if (gMaxChan > 0)
    delay(500); //long pause if OK
  else
    delay(50); //rapid blink if error
  digitalWrite(kPIN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500); */
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

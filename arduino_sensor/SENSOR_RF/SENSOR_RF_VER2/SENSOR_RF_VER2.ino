//Transmitter program

#include "nRF24L01.h"
Nrf24l Mirf = Nrf24l(10, 9);
byte value[4];

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
    Mirf.setTADDR((byte *)"MotorDriver");
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
}

void loop()
{
  value[0] = analogRead(A0);
  value[1] = analogRead(A0);
  value[2] = analogRead(A0);
  //value[3] = random(255);                      //0-255 random number
  value[3] = analogRead(A0);
  Mirf.send(value);                //Send instructions, send random number value
  Serial.println("Wait for sending.....");
  while (Mirf.isSending())//Until you send successfully, exit the loop
  delay(1);
  Serial.print("Send success:");
  Serial.println(value[3]);
  delay(10);
}

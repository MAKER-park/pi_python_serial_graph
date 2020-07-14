/*
 * adsCMD.h
 * Library header file for adsCMD library
 */

#include "Arduino.h"

const int dataReadyPin = 17;
const int chipSelectPin = 5;


//function prototypes
void adc_wreg(int reg, int val); //write register
void adc_send_command(int cmd); //send command
int adc_rreg(int reg); //read register

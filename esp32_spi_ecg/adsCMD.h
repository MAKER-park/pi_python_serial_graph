/*
 * adsCMD.h
 * Library header file for adsCMD library
 */

#include "Arduino.h"

const int IPIN_PWDN = 2; //not required for TI demo kit
const int IPIN_RESET  = 4;//*optional
const int PIN_START = 16;
const int dataReadyPin = 5;
const int chipSelectPin = 17;


//function prototypes
void adc_wreg(int reg, int val); //write register
void adc_send_command(int cmd); //send command
int adc_rreg(int reg); //read register

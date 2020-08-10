
// Display EKG, tested to 1,000x/sec

import processing.serial.*;
Serial myPort;

int EKG_signal;
int EKG_old;                    // last data
int y,t;                        // Y, Time
int timebase = 1;               // timebase of display

void setup() {
  size(1400, 280);              // x,y
  background(200, 0, 0);        // Red, Green, Blue
  printArray(Serial.list());    // serial ports available
  myPort = new Serial(this, Serial.list()[0], 9600);// set up serial port
}

void draw() {                    // main loop
  while (myPort.available()>0){  // if char available...
    EKG_signal = 0;              // zero accumulator
    for(int i=0; i<timebase; i++) EKG_signal += myPort.read(); // accumulate bytes
    EKG_signal = EKG_signal/timebase;  // reduce to byte size
    t = t + 1;                   // increment time axis
    if(t>width) t=0;             // reset pointer
    stroke(255);                 // change to line color
    line(t-1,height-EKG_old, t,height-EKG_signal);// line from last datapoint to new one
    fill(200,0,0);               // background color
    noStroke();                  // disable rectangle outline
    rect(t+1,0,50,height);       // UL, W, H, overwrite ahead of EKG signal
  }
  EKG_old = EKG_signal;          // save newest datapoint
}

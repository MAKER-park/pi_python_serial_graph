// EKG simulator, simulates EKG wave at 1000x/sec -> 60 Beats Per Minute
// Waveform is created from an array of 50 data points to create the PQRST complex
// each data point is sent 10 times
// Baseline between pulses is sent 50x
//              1   2   3   4   5   6   7   8   9  10 
byte EKG[51] = {40, 38, 42, 43, 44, 45, 44, 43 ,42, 41,
               40, 40, 40, 40, 40, 39, 42, 43, 60, 80,
               100,120,80, 50,  5, 10, 20, 30, 40, 50,
               35, 40, 41, 42, 43, 44, 45, 46, 47, 48,
               49, 50, 51, 51, 50, 49, 48, 45, 42, 40, 40}; // 50 PQRST wave datapoints

byte y,t;                                   // Y axis, time
void setup() {
  Serial.begin(115200);                       // 9600 Baud
  //pinMode(LED_BUILTIN,OUTPUT);              // blink LED to signal life
}

void loop() {
  t = t+1;                                  // increment time
  if(t > 100) {                             // if 100 data points sent, reset pointer
    t=0;
    //digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  }
  if(t<50) {                                // first 50 data points come from array
    for(int i=0; i<10; i++){                // send each array data point 10x
      y = EKG[t]+ random(-3,3);             // add noise 
      y = y + i*((EKG[t+1] - EKG[t])/10);   // interpolate between datapoints to smooth
      y = constrain(y,0,255);               // make sure not bigger than byte
      Serial.write(y);                      // send byte
    }
  }
  else {
    for(int i=0; i<10; i++){
      Serial.write(y);// send 10x fifty times
      y =  40 + random(-2,2);                // baseline + noise
    }
  }
  delay(100);
}

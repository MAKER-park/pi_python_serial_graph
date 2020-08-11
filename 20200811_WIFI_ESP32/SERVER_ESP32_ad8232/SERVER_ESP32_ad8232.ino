#include "WiFi.h"
#include "ESPAsyncWebServer.h"


#include <Wire.h>


int adc = map(analogRead(36),0,4095,0,1024);

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readADC() {
  /*if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    //Serial.println('!');
    return String("0");
  }
  else{
    // send the value of analog input 0:
      //Serial.println(analogRead(15));
      return String(analogRead(15));
  }*/

  
    return String(adc);
  //return String(analogRead(21));
  //return String(random(0,1024));
  //return String(1.8 * bme.readTemperature() + 32);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/readADC", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readADC().c_str());
  });
  // Start server
  server.begin();

  pinMode(19, INPUT); // Setup for leads off detection miso LO +
  pinMode(18, INPUT); // Setup for leads off detection sclk LO -
  //pinMode(15, INPUT); // Setup for leads off detection cs output
  pinMode(5, OUTPUT); // Setup for leads off detection start 3.3v
  pinMode(17, OUTPUT); // Setup for leads off detection rst  gnd
  digitalWrite(17, LOW);
  digitalWrite(5, HIGH);
}
 
void loop(){
  /*if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      Serial.println(analogRead(15));
  }*/
  digitalWrite(17, LOW);
  digitalWrite(5, HIGH);

  adc = map(analogRead(36),0,4095,0,1024);
  
  Serial.println(adc);
  //delay(1);
}

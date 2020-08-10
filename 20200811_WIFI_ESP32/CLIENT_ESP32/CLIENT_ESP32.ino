#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNamereadADC = "http://192.168.4.1/readADC";

#include <Wire.h>


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

String readADC;

unsigned long previousMillis = 0;
const long interval = 10; 

void setup() {
  Serial.begin(115200);
   
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      readADC = httpGETRequest(serverNamereadADC);
      //Serial.println("Temperature: " + temperature + " *C - Humidity: " + humidity + " % - Pressure: " + pressure + " hPa");
      // save the last HTTP GET Request
      Serial.println(readADC);
      previousMillis = currentMillis;
    }
    else {
      //Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

/* 
  Rui Santos 
  Complete project details at https://RandomNerdTutorials.com/esp8266-client-server-wi-fi/ 
   
  Permission is hereby granted, free of charge, to any person obtaining a copy 
  of this software and associated documentation files. 
   
  The above copyright notice and this permission notice shall be included in all 
  copies or substantial portions of the Software. 
*/ 
 
#include <WiFi.h> 
#include <HTTPClient.h> 
#include <WiFiClient.h> 
 
#include <ESP8266WiFiMulti.h> 
ESP8266WiFiMulti WiFiMulti; 
 
const char* ssid = "ESP8266-Access-Point"; 
const char* password = "123456789"; 
 
//Your IP address or domain name with URL path 
const char* serverNameTemp = "http://192.168.4.1/temperature"; 
 
 
#include <Wire.h> 
 
String temperature; 
 
 
 
void setup() { 
  Serial.begin(115200); 
  Serial.println(); 
   
  
  WiFi.mode(WIFI_STA); 
  WiFiMulti.addAP(ssid, password); 
  while((WiFiMulti.run() == WL_CONNECTED)) {  
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(""); 
  Serial.println("Connected to WiFi"); 
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH); 
} 
 
void loop() { 
 
     // Check WiFi connection status 
    if ((WiFiMulti.run() == WL_CONNECTED)) { 
      temperature = httpGETRequest(serverNameTemp); 
      //Serial.println("Temperature: " + temperature );
      Serial.println(temperature ); 
 
       
      // save the last HTTP GET Request 
    } 
    else { 
      Serial.println("WiFi Disconnected"); 
    } 
} 
 
String httpGETRequest(const char* serverName) { 
  WiFiClient client; 
  HTTPClient http; 
     
  // Your IP address with path or Domain name with URL path  
  http.begin(client, serverName); 
   
  // Send HTTP POST request 
  int httpResponseCode = http.GET(); 
   
  String payload = "--";  
  digitalWrite(LED_BUILTIN, LOW);   
   
  if (httpResponseCode>0) { 
    //Serial.print("HTTP Response code: "); 
    //Serial.println(httpResponseCode); 
    payload = http.getString(); 
    digitalWrite(LED_BUILTIN, HIGH); 
  } 
  else { 
    Serial.print("Error code: "); 
    Serial.println(httpResponseCode); 
  } 
  // Free resources 
  http.end(); 
 
  return payload; 
} 

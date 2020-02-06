/*
    Wireless Serial using UDP ESP8266
    Hardware: NodeMCU
    Circuits4you.com
    2018
    Slave Board connects to Access Point
    https://circuits4you.com/2018/01/01/esp-to-esp-communication/
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "circuits4you";
const char *pass = "password"; 

unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

char packetBuffer[9];   //Where we get the UDP data
//======================================================================
//                Setup
//======================================================================
void send_data(){
  udp.beginPacket(ServerIP, 2000);  //Send Data to Master unit
  //Send UDP requests are to port 2000
        
  char a[1];
  //a[0]=char(Serial.read()); //Serial Byte Read
  a[0]=char('a'); //Serial Byte Read
  //Serial.println(a[0]);
  udp.write(a,1); //Send one byte to ESP8266 
  udp.endPacket();
}
void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println();

    WiFi.begin(ssid, pass);   //Connect to access point
  
    Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
    int cb = udp.parsePacket();
    digitalWrite(LED_BUILTIN, HIGH);
    
    if (!cb) 
    {
      send_data();
      
      //If serial data is recived send it to UDP

      
      /*if(Serial.available()>0)
        {
        udp.beginPacket(ServerIP, 2000);  //Send Data to Master unit
        //Send UDP requests are to port 2000
        
        char a[1];
        a[0]=char(Serial.read()); //Serial Byte Read
        udp.write(a,1); //Send one byte to ESP8266 
        udp.endPacket();
        }*/
    }
    else {
      // We've received a UDP packet, send it to serial
      udp.read(packetBuffer, 1); // read the packet into the buffer, we are reading only one byte
      Serial.print(packetBuffer);
      delay(20);
    }
}
//=======================================================================

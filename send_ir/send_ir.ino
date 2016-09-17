/* 
 *  Send IR command to a FUJITSU AC
 */

#include <Arduino.h>
#include <FujitsuHeatpumpIR.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "sagem";
const char* password = "superclave";
WiFiServer server(80);
int ledPin = 5; //D1

//NodeMCU pinout
/*
https://pradeepsinghblog.files.wordpress.com/2016/04/nodemcu_pins.png?w=616
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
*/

#ifndef ESP8266
IRSenderPWM irSender(3);       // IR led on Arduino digital pin 3, using Arduino PWM
//IRSenderBlaster irSender(3); // IR led on Arduino digital pin 3, using IR Blaster (generates the 38 kHz carrier)
#else
IRSenderBitBang irSender(5);   // IR led on ESP8266 GPIO pin 1
#endif


// Array with all supported heatpumps
HeatpumpIR *heatpumpIR = new FujitsuHeatpumpIR();
//FujitsuHeatpumpIR  heatpumpIR();

void setup()
{
  Serial.begin(9600);
  delay(500);

// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

byte mac[6];
WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  //Serial.println(F("Starting"));
}

void loop()
{
  int i = 0;
  const char* buf;

// Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/AC=ON") != -1)  {
    //digitalWrite(ledPin, HIGH);
    value = HIGH;
    heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_2, 24, VDIR_UP, HDIR_AUTO);
  }
  if (request.indexOf("/AC=OFF") != -1)  {
    //digitalWrite(ledPin, LOW);
    value = LOW;
      // Send the IR command
    heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_2, 24, VDIR_UP, HDIR_AUTO);
  }
  
  
  buf = heatpumpIR->model();
  // 'model' is a PROGMEM pointer, so need to write a byte at a time
  /*
  while (char modelChar = pgm_read_byte(buf++))
  {
  Serial.print(modelChar);
  }
  Serial.print(F(", info: "));
*/
  buf = heatpumpIR->info();
  // 'info' is a PROGMEM pointer, so need to write a byte at a time
  /*while (char infoChar = pgm_read_byte(buf++))
  {
    Serial.print(infoChar);
  }
  Serial.println();
*/

  

client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (value)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
 
 
}

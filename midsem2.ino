/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include "htmlPage.h"
#define SOUND_SPEED 0.034


unsigned long prevTime_T1 = millis();
long interval_T1 = 300;
unsigned long prevTime_T2 = millis();
long interval_T2 = 300;
unsigned long prevTime_T3 = millis();
long interval_T3 = 300;
unsigned long prevTime_T4 = millis();
long interval_T4 = 300;

const int trigPin = 5;
const int echoPin = 18;
int led = 15;
int relay = 14;
int pin = 23;
long duration;
float distanceCm;

int auto_state = 0;     //0 for auto 1 for manual off 2 for manual on

//const char* ssid = "DUFIE-HOSTEL";
//const char* password = "Duf1e@9723";


//const char* ssid = "Ben.Fra.Pri";
//const char* password = "M633SFTK";

//const char* ssid = "Millz";
//const char* password = "nanayaw22";

const char* ssid = "S8";
const char* password = "Pakus+12";

WebServer server(80);

WiFiMulti wifiMulti;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void handleRoot() {
  server.send(200, "text/html", theHtmlCode);
}

void handleWaterLevel(){
  server.send(200, "text/plain",String(distanceCm) );
}


void waterlevels(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
    distanceCm = duration * SOUND_SPEED/2;  // Calculate the distance
  
    String water_reading = String(distanceCm);
    server.send(200, "text/plain", water_reading);
}


void handleNotFound() {
  //digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  //digitalWrite(led, 0);
}


void autoMode(){
  auto_state = 0;  
}

void manStart(){
  auto_state = 2;  
}


void manStop(){
  auto_state = 1;  
}


void setup(void) {
    Serial.begin(115200);
    
    lcd.init();
    lcd.clear();         
    lcd.backlight();      // Make sure backlight is on
    
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(led, OUTPUT); // Sets the trigPin as an Output
    pinMode(relay, OUTPUT); // Sets the trigPin as an Output
    
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.println();
    Serial.println();
    Serial.println();

    // another way to check the connection
    while(WiFi.status() != WL_CONNECTED){
      delay(200);
      Serial.print(".");
    }

    wifiMulti.addAP(ssid, password);

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

//    if (MDNS.begin("esp32")) {
//    Serial.println("MDNS responder started");
//    }

    server.on("/", handleRoot);
    server.on("/waterlevels", waterlevels);
    server.on("/autoMode", autoMode);
    server.on("/manStart", manStart);
    server.on("/manStop", manStop);
    server.on("/theWaterLevel", handleWaterLevel);
//    });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void loop(void) {   
    unsigned long currentTime = millis();
    if(currentTime - prevTime_T3 > interval_T3){
      waterlevels();
      prevTime_T3 = currentTime;
    }

      if(auto_state==0){
        if(distanceCm <= 10){
          digitalWrite(led,HIGH);
          digitalWrite(relay,HIGH);
          server.send(200, "text/plain");
       }
  
       if(distanceCm >= 20){
        digitalWrite(led,LOW);
        digitalWrite(relay,LOW);
        server.send(200, "text/plain");
       }
     }
     
      else if(auto_state==1){
        digitalWrite(led,LOW);
        digitalWrite(relay,LOW);
        server.send(200, "text/plain"); 
      }
      else if(auto_state==2){
       digitalWrite(led,HIGH);
       digitalWrite(relay,HIGH);
       server.send(200, "text/plain");
      }
 

    if(currentTime - prevTime_T2 > interval_T2){
      // Print a message on both lines of the LCD.
      lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
      lcd.print("Water Level");
    
      lcd.setCursor(5,1);   //Move cursor to character 2 on line 1
      lcd.print(distanceCm);

      Serial.print("Distance (cm): ");
      Serial.println(distanceCm);
      
      prevTime_T2 = currentTime;
    }

    
      server.handleClient();

   if(currentTime - prevTime_T1 > interval_T1){
     // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://192.168.43.99/iot/midsem.php?DistanceCm="+String (distanceCm)); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    prevTime_T1 = currentTime;}
  
}

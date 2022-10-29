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
#define SOUND_SPEED 0.034
const int trigPin = 5;
const int echoPin = 18;
int led = 15;
long duration;
float distanceCm;

const char* ssid = "DUFIE-HOSTEL";
const char* password = "Duf1e@9723";
WebServer server(80);

WiFiMulti wifiMulti;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {

    lcd.init();
    lcd.clear();         
    lcd.backlight();      // Make sure backlight is on
    
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(led, OUTPUT); // Sets the trigPin as an Output
    
    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.println();

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    wifiMulti.addAP("DUFIE-HOSTEL", "Duf1e@9723");

}

void loop() {

    digitalWrite(led, HIGH);
   // Print a message on both lines of the LCD.
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("Water Level");
  
    lcd.setCursor(5,1);   //Move cursor to character 2 on line 1
    lcd.print(distanceCm);
    lcd.print("cm");

    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
    distanceCm = duration * SOUND_SPEED/2;  // Calculate the distance

    // turns on the led when the water level is below 5cm 
    if(distanceCm < 20){
      digitalWrite(led, HIGH);   // turn the led on

    }else {
      digitalWrite(led, LOW);    // turn the led off
    }

    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://192.168.102.13/iot/midsem.php?DistanceCm="+String (distanceCm)); //HTTP

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

    delay(2000);
}

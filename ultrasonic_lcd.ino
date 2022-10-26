#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int trigPin = 5;
const int echoPin = 18;
int led = 4; // set the "led" variable as 4


//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;


void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(led, OUTPUT);   // designate port 4 as output
  
  
}

void loop() {
   // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Water Level");
  
  lcd.setCursor(5,1);   //Move cursor to character 2 on line 1
  lcd.print(distanceCm);
  lcd.print("cm");

   
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  // turns on the led when the water level is below 5cm 
  if(distanceCm < 20){
    digitalWrite(led, HIGH);   // turn the led on

   }else {
    digitalWrite(led, LOW);    // turn the led off
   }
   
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  delay(1000);
  lcd.clear();
}
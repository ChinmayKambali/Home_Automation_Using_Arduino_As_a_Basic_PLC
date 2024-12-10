#include <DHT.h>
#define DHTPIN 2 //Sensor Pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
int speakerpin=4; 
int push=8;
int ledPin = 7;                // choose the pin for the LED
int PIRinputPin = 3;            // choose the input pin (for PIR sensor)
int PIRState = LOW;             // we start, assuming no motion detected
int val = 0;   
int val1;  
float temp;                     // variable for reading the pin status
const int redPin = 5;           // Red LED connected to digital pin 9
const int greenPin = 6;        // Green LED connected to digital pin 10
const int bluePin = 9;         // Blue LED connected to digital pin 11

void setColor(int redValue, int greenValue, int blueValue)
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void setup() 
{
  pinMode(speakerpin, OUTPUT);
  pinMode(ledPin, OUTPUT);      
  pinMode(PIRinputPin, INPUT);  
  pinMode(push, INPUT_PULLUP);  
  pinMode(redPin, OUTPUT);      
  pinMode(greenPin, OUTPUT);    
  pinMode(bluePin, OUTPUT);     
  Serial.begin(9600);           
  dht.begin();
}

void loop() 
{
    val1=digitalRead(push);
    Serial.println(val1); 
if(val1==1)
    {   
      digitalWrite(speakerpin, HIGH);  // turn LED ON
      }
    else  
      {
     digitalWrite(speakerpin, LOW);  // turn LED ON  
        }
 float humi = dht.readHumidity();
    float temp = dht.readTemperature(); 
    String state = String((float)temp)+" C"+"|"+String((float)humi)+" %";
    Serial.println(state);
    val = digitalRead(PIRinputPin);
 
  if (val == HIGH)  // check if the PIR sensor detected motion
  {
    digitalWrite(ledPin, HIGH);  // turn LED ON
  
  }
  else if(val == LOW)
  {
    digitalWrite(ledPin, LOW);  // turn LED ON
  
    }

     else if ((temp >= 20) && (temp < 24)) 
      {
        setColor(255, 0, 0);  // Red
      } 
      else if ((temp >= 24) && (temp < 28)) 
      {
        setColor(0, 255, 0);  // Green
      } 
      else if ((temp >= 28) && (temp < 30)) 
      {
        setColor(0, 0, 255);  // Blue
      } 
      else if ((temp >= 30) && (temp < 34)) 
      {
        setColor(255, 165, 0);  // Orange
      } 
      else if (temp >= 34) 
      {
        setColor(165, 42, 42);  // Brown
      } 
      else 
      {
        setColor(255, 192, 203);  // Pink for temp below 20
      //  digitalWrite(speakerpin, LOW);
      }
 
 delay(2000);  // Wait for 5 seconds
      setColor(0, 0, 0);  // Turn off the LED after 5 seconds
}

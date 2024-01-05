#include <FastLED.h>

const int trigPin = 5;
const int ledPin = 4;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#define NUM_LEDS     60
//#define BRIGHTNESS          155

long duration;
float distanceCm;
float distanceInch;
CRGB leds[NUM_LEDS];
//CRGB currentColour;
CRGBPalette16 myPalette = RainbowStripesColors_p;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  FastLED.addLeds<WS2812B, ledPin, GRB>(leds, NUM_LEDS);
  //FastLED.setBrightness(BRIGHTNESS);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  fill_solid(leds, NUM_LEDS, ColorFromPalette(myPalette, 128));
  //currentColour = CRGB::White;
  FastLED.show();
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
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
  //FastLED.delay(10);
  if (distanceCm >= 250.0){
    fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 160, 0, LINEARBLEND));
    FastLED.show();
    Serial.print("Setting LEDs to Blue");
  }
    else if (distanceCm < 250.0 && distanceCm >= 150.0){
    fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 96, 205, LINEARBLEND));
    FastLED.show();
    Serial.print("Setting LEDs to Green");
  }
  else if (distanceCm < 150.0 && distanceCm >= 80.0){
    fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 64, 205, LINEARBLEND));
    FastLED.show();
    Serial.print("Setting LEDs to Yellow");
  }
  else if (distanceCm < 80.0 && distanceCm >= 50.0){
    fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 0, 205, LINEARBLEND));
    FastLED.show();
    Serial.print("Setting LEDs to Red");
  }
  else if (distanceCm < 50.0 && distanceCm >= 25.0){
      fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 0, 205, LINEARBLEND));
      FastLED.show();
      delay(150);
      // Now turn the LED off, then pause
      fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 0, 0, LINEARBLEND));
      FastLED.show();
      delay(50);
  }
  else if (distanceCm < 25.0)
  {
    // Turn off the strip, the car is close enough
    fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 0, 0, LINEARBLEND));
    FastLED.show();
    Serial.print("Setting LEDs to Black");
  }
  else{
    // Something is wrong, but nothing major
    fill_solid( leds, NUM_LEDS, ColorFromPalette(myPalette, 0, 0, LINEARBLEND));
    FastLED.show();
    Serial.print("Setting LEDs to Black");
  }
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(200);
}
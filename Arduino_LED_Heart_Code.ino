
/*  PulseSensor Starter Project and Signal Tester
    The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.

    Here is a link to the tutorial
    https://pulsesensor.com/pages/code-and-guide

    WATCH ME (Tutorial Video):
    https://www.youtube.com/watch?v=RbB8NSRa5X4


  -------------------------------------------------------------
  1) This shows a live human Heartbeat Pulse.
  2) Live visualization in Arduino's Cool "Serial Plotter".
  3) Blink an LED on each Heartbeat.
  4) This is the direct Pulse Sensor's Signal.
  5) A great first-step in troubleshooting your circuit and connections.
  6) "Human-readable" code that is newbie friendly."

*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);


//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 511;            // Determine which Signal to "count as a beat", and which to ingore.

float currentLEDNum = 0;

// The SetUp Function:
void setup() {
  pinMode(LED13, OUTPUT);        // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
  // Assign this value to the "Signal" variable.

  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.


  if (Signal > Threshold) {                        // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED13, HIGH);
    currentLEDNum = 0;
    //colorWipe(strip.Color(255, 0, 0), 5);
  } else {
    digitalWrite(LED13, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
  }

  heartBeatWipe();

  delay(10);


}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    if (i > 5) {

      strip.setPixelColor(i - 6, strip.Color(0, 0, 0));

    }
    delay(wait);
  }
}


void heartBeatWipe() {
  for (uint16_t i = 0; i < 30; /*strip.numPixels();*/ i++) {

    if (currentLEDNum == i) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  strip.show();

  currentLEDNum++;
  //  if (i > 5) {
  //
  //    strip.setPixelColor(i - 6, strip.Color(0, 0, 0));
  //
  //  }
  //  delay(wait);
}

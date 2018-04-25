#include <FastLED.h>
#define NUM_LEDS 49

CRGB leds[NUM_LEDS];
String data = "";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
}

void loop() {
  delay(10);
  // if there is data waiting to be read
  if (Serial.available() > 0) {
    // loop through the data bytes and add it to a string
    while (Serial.available() > 0) {
      data += char(Serial.read());
    }
    
    // if the full data string has been recieved
    if (data.length() == 8) {
      Serial.println(data);
      // get colour hex code, convert to number then get individual values
      String color = data.substring(0, 6);
      long colorData = strtol( &color[0], NULL, 16);
      long r = colorData >> 16;
      long g = colorData >> 8 & 0xFF;
      long b = colorData & 0xFF;

      // get last two characters from data and convert to number
      String location = data.substring(6, 8);
      int l = location.toInt();

      // set LED colour at location
      leds[l].setRGB(r, g, b);
      FastLED.show();
      
      // clear data for next input
      data = "";
    }
  }
}

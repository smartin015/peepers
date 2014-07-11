#include <Adafruit_NeoPixel.h>

int rgbState = 0;
#define RGB_STATE_IDLE = 1;

int pixels[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int count = 0;
int curPixelVal = 1;
int curColor = 2;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup_RGB() {
  strip.begin();
  
  colorWipe(strip.Color(0, 0, 0), 4);
  strip.show();
}
/*
void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}*/

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void clearRGBStrip()
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
  }
}

void setRGBStripColor(int red, int green, int blue)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(red,green,blue));
      strip.show();
  }
}

void setRGBPixelColor(int red, int green, int blue, int pixel)
{
  strip.setPixelColor(pixel, strip.Color(red,green,blue));
  strip.show();
}

void setRGBPixelQueue(int red, int green, int blue, int pixel)
{
  strip.setPixelColor(pixel, strip.Color(red,green,blue));
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void setRGBStripColor(int col, int colval)
{
  if(col == 0)
  {
    colorWipe(strip.Color(colval, 0, 0), 4);
  }
  else if(col == 1)
  {
    colorWipe(strip.Color(0, colval, 0), 4);
  }
  else
  {
    colorWipe(strip.Color(0, 0, colval), 4);
  }
  
  strip.show();
}

void test_rgb() {
  Serial.println("RGB rainbow pattern");
  delay(500);
  rainbow(20);
  colorWipe(strip.Color(0, 0, 0), 50);
}

unsigned long rgbDelay = 50;
unsigned long lastRGBTime;
int rgbIncrement = 1;
int maxRGBVal = 255;

void init_rgb_fade(int col, int rgbincrement, int maxrgbval, unsigned long rgbdelay) 
{
  lastRGBTime = millis();
  rgbDelay = rgbdelay;
  rgbIncrement = rgbincrement;
  curPixelVal = 0;
  curColor = col;
  maxRGBVal = maxrgbval;
}

void update_rgb_fade()
{
  /*
    IF it difference between (the last millis() it updated), and (current millis())
    is greater than ledbarDelay, then increment curPixelVal, and set lastRGBTime 
    to current millis()
  */
  if((millis()-lastRGBTime)>rgbDelay)
  {
    if(curPixelVal >= maxRGBVal)
    {
      curPixelVal = 0;
    }
    for(int i = 0; i < NUM_LEDS; i ++)
    {
      pixels[i][curColor] = curPixelVal;
    }
    //clearRGBStrip();
    setRGBStripColor(curColor,curPixelVal);
    curPixelVal += rgbIncrement;
    lastRGBTime = millis();
  }
}

void init_rgb_flash(int col, int maxrgbval, unsigned long rgbdelay)
{
  lastRGBTime = millis();
  rgbDelay = rgbdelay;
  curPixelVal = 0;
  curColor = col;
  maxRGBVal = maxrgbval;
}

void update_rgb_flash()
{
  if((millis()-lastRGBTime)>rgbDelay)
  {
    if(curPixelVal == 0)
    {
      curPixelVal = maxRGBVal;
    }
    else
    {
      curPixelVal = 0;
    }
    setRGBStripColor(curColor, curPixelVal);
    lastRGBTime = millis();
  }
}

/*
void update_rgb_idle()
{
  int prevPixel = curPixelVal;
  clearRGBStrip();
  strip.setPixelColor(curPixelVal, strip.Color(pixels[curPixelVal][0],pixels[curPixelVal][1],pixels[curPixelVal][2]));
  strip.show();
  
  Serial.print("Pixel: ");
  Serial.print((int)curPixelVal);
  Serial.print(" Color: ");
  Serial.print((int)curColor);
  Serial.print(" Value: ");
  Serial.println((int)pixels[curPixelVal][curColor]);
  if(pixels[curPixelVal][curColor] >= 255)
  {
    pixels[curPixelVal][curColor] = 0;
    while(prevPixel == curPixelVal) {
       curPixelVal =  (int) random(0, 3);
    }
    //clearRGBStrip();
  }
  else
  {
    pixels[curPixelVal][curColor] += 5;
  }
}*/

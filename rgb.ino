
#ifdef RGB_STRIP
class RGBStrip
{
  public:

    int rgbState;
    int pixels[4][3];
    int count;
    int curPixelVal;
    RGBColor curColor;
    unsigned long rgbDelay;
    unsigned long lastRGBTime;
    int rgbIncrement;
    int maxRGBVal;
    Adafruit_NeoPixel *strip;
    
    RGBStrip()
    {
       rgbState = 0;
       count = 0;
       curPixelVal = 1;
       curColor = RGB_GREEN;
       rgbDelay = 50;
       lastRGBTime = 0;
       rgbIncrement = 1;
       maxRGBVal = 255;
       strip = new Adafruit_NeoPixel(NUM_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);
       strip->begin();
       //colorWipe(strip->Color(0, 0, 0), 4);
       //strip->show();
    }
     
    
    void test_rgb() {
      Serial.println("RGB rainbow pattern");
      delay(500);
      colorWipe(strip->Color(0, 0, 0), 50);
    }
    
    void init_rgb_flash(RGBColor col, int maxrgbval, unsigned long rgbdelay)
    {
      //DEBUG_PRINT("RGB Val initialized to " + maxrgbval);
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
    
    
    int minRGBVal;
    
    void init_rgb_fade(RGBColor col, int minrgbval, int maxrgbval, int rgbincrement, unsigned long rgbdelay)
    {
      rgbIncrement = rgbincrement;
      lastRGBTime = millis();
      rgbDelay = rgbdelay;
      curPixelVal = 20;
      curColor = col;
      maxRGBVal = maxrgbval;
      minRGBVal = minrgbval;
    }
    
    void update_rgb_fade()
    {
      //if((millis()-lastRGBTime)>rgbDelay)
      //{
        
        curPixelVal += rgbIncrement;
        setRGBStripColor(curColor, curPixelVal);
        DEBUG_PRINT(curPixelVal);
        //lastRGBTime = millis();
        if((curPixelVal + rgbIncrement)>maxRGBVal||(curPixelVal + rgbIncrement)< minRGBVal)
        {
          rgbIncrement *= -1;
        }
      //}
    }
    
    // Parameter 1 = number of pixels in strip
    // Parameter 2 = Arduino pin number (most are valid)
    // Parameter 3 = pixel type flags, add together as needed:
    
    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait) {
      for(uint16_t i=0; i<strip->numPixels(); i++) {
          strip->setPixelColor(i, c);
          strip->show();
          delay(wait);
      }
    }
    
    void clearRGBStrip()
    {
      for(uint16_t i=0; i<strip->numPixels(); i++) {
          strip->setPixelColor(i, strip->Color(0,0,0));
          strip->show();
      }
    }
    
    void setRGBStripColor(int red, int green, int blue)
    {
      
      for(uint16_t i=0; i<strip->numPixels(); i++) {
          strip->setPixelColor(i, strip->Color(red,green,blue));
      }
      strip->show();
    }
    
    void setRGBPixelColor(int red, int green, int blue, int pixel)
    {
      strip->setPixelColor(pixel, strip->Color(red,green,blue));
      strip->show();
    }
    
    
 
    
    
    void setRGBStripColor(RGBColor col, int colval)
    {
      String currentColor = col + "";
      //DEBUG_PRINT("Set RGB color to : " + currentColor);
      if(col == RGB_RED)
      {
        colorWipe(strip->Color(colval, 0, 0), 4);
        DEBUG_PRINT("RGB set RED");
      }
      else if(col == RGB_GREEN)
      {
        colorWipe(strip->Color(0, colval, 0), 4);
        DEBUG_PRINT("RGB set GREEN");
      }
      else if(col == RGB_BLUE)
      {
        colorWipe(strip->Color(0, 0, colval), 4);
        DEBUG_PRINT("RGB set BLUE");
      }
      else
      {
        DEBUG_PRINT("Incorrect RGB color set");
      }
      
      strip->show();
    }
};
#endif

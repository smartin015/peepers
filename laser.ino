class LaserControl
{
  public:
    int laserPin;
    LaserControl()
    {
      laserPin = LASER_PIN;
      pinMode(laserPin, OUTPUT);
    }
    void laserOn() {
      digitalWrite(laserPin, HIGH);
    }
    
    void laserOff() {
      digitalWrite(laserPin, LOW);
    }
    
    void test_laser() {
      Serial.println("Laser On");
      delay(500);
      laserOn();
      delay(1000);
      Serial.println("Laser Off");
      delay(500);
      laserOff();
    }
    
    void init_laser_idle()
    {
      digitalWrite(laserPin, LOW);
    }
    
    void update_laser_idle()
    {
      digitalWrite(laserPin, LOW);
    }
    
    unsigned long lastLaserTime;
    unsigned long laserDelay;
    unsigned long tempMillis;
    
    void init_laser_flash(unsigned long laserdelay)
    {
      laserDelay = laserdelay;
      lastLaserTime = millis();
      digitalWrite(laserPin, LOW);
    }
    
    void update_laser_flash()
    {
      tempMillis = millis();
      if((laserDelay-200)<(tempMillis-lastLaserTime)&&(tempMillis-lastLaserTime)<(laserDelay+200))
      {
        digitalWrite(laserPin, HIGH);
        //DEBUG_PRINT("Fire Laser");
        if((tempMillis-lastLaserTime)>laserDelay)
        {
          lastLaserTime = millis();
        }
      }
      else
      {
        digitalWrite(laserPin, LOW);
      }
    }
};

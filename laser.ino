int laserPin;

void setup_LASER(int pin) {
  laserPin = pin;
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

void init_laser_flash(unsigned long laserdelay)
{
  laserDelay = laserdelay;
  lastLaserTime = millis();
  digitalWrite(laserPin, LOW);
}

void update_laser_flash()
{
  unsigned long tempMillis = millis();
  if((laserDelay-100)<(tempMillis-lastLaserTime)&&(tempMillis-lastLaserTime)<(laserDelay+100))
  {
    digitalWrite(laserPin, HIGH);
    Serial.println("FIRIN MUH LASER");
    Serial.println(" ");
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

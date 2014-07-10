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

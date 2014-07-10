int servoPin;

int angle;
int pwm;

int pos = 0;    // variable to store the servo position 

void setup_SERVO(int pin) {
  servoPin = pin;
  pinMode(servoPin, OUTPUT);
}

void setServoPosition(int newPos, int increment) {
  
  if(newPos > pos) {
    for (angle = pos; angle <= newPos; angle += increment)  {
      servoPulse(servoPin, angle);  
    }
  }
  else if(newPos < pos) {
    for (angle = pos; angle >= newPos; angle -= increment)  {
      servoPulse(servoPin, angle);  
    }
  }
  pos = newPos;  
}

int getServoPosition() {
  return pos;
}

void servoPulse (int servo, int angle)
{
  pwm = (angle*11) + 500;      // Convert angle to microseconds
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(servo, LOW);
  delay(50);                   // Refresh cycle of servo
}

void test_servo() {
  Serial.println("Servo to 140");
  delay(500);
  setServoPosition(140, 10);
  delay(1000);
  Serial.println("Servo to 0");
  delay(500);
  setServoPosition(0, 10);
}

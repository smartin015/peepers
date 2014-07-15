class ServoControl
{
  public:
    ServoControl()
    {
      lastServoPulseMillis = millis();
      curServoPulseMillis = millis();
      servoPin = SERVO_PIN;
      pinMode(servoPin, OUTPUT);
      pos = 0; 
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
    
    int servoPin;
    
    int angle;
    int pwm;
    
    int pos;    // variable to store the servo position 
    
    
    unsigned long lastServoPulseMillis;
    unsigned long curServoPulseMillis;
    
    void setServoPosition(int newPos, int inc) {
      
      if(newPos > pos) {
        for (angle = pos; angle <= newPos; angle += inc)  {
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
    
    void incrementServo(int inc, int dir)
    {
      
      if(dir == 1)
      {
        pos += inc;
        servoPulse(servoPin, (getServoPosition() + inc));
      }
      else
      {
        pos -= inc;
        servoPulse(servoPin, (getServoPosition() - inc));
      }
      
    }
    
    int getServoPosition() {
      return pos;
    }
    
    void servoPulse (int servo, int angle)
    {
      
      curServoPulseMillis = millis();
      if (curServoPulseMillis >= lastServoPulseMillis + 50)
      {
        pwm = (angle*11) + 500;      // Convert angle to microseconds
        cli();
        digitalWrite(servo, HIGH);
        delayMicroseconds(pwm);
        digitalWrite(servo, LOW);
        sei();
        delay(25);                   // Refresh cycle of servo
        lastServoPulseMillis = curServoPulseMillis;
      }
    }
    
    int pos1;
    int pos2;
    int dest;
    int increment;
    unsigned long servoDelay;
    unsigned long lastServoTime; 
    
    void init_servo_agitated(int p1, int p2, int inc, unsigned long servodelay)
    {
      pos1 = p1;
      pos2 = p2;
      increment = inc;
      servoDelay = servodelay;
      lastServoTime = 0;
      if(getServoPosition() <= pos1)
      {
        dest = pos2;
      }
      else if (getServoPosition() >= pos2)
      {
        dest = pos1;
      }
    }
    
    void update_servo_agitated()
    {
      if(getServoPosition() <= pos1)
      {
        //DEBUG_PRINT("hit pos1");
        dest = pos2;
        servoPulse(servoPin, getServoPosition());
      }
      else if (getServoPosition() >= pos2)
      {
        //DEBUG_PRINT("hit pos2");
        dest = pos1;
        servoPulse(servoPin, getServoPosition());
      }
      else
      {
        servoPulse(servoPin, getServoPosition()); 
      }
      
      if(dest > getServoPosition())
      {
        //setServoPosition(getServoPosition() + increment, increment);
        incrementServo(increment,1);
        //curpos += increment;
      }
      else
      {
        //setServoPosition(getServoPosition() - increment, increment);
        incrementServo(increment,0);
        //curpos -= increment;
      }
      //DEBUG_PRINT(getServoPosition());
      //if((millis()-lastServoTime)>servoDelay)
    }
};


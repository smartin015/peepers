
RGBStrip rgbStrip;
RFControl rfControl;
LEDBar ledBar;
ServoControl servoControl;
LaserControl laserControl;
CapSenseControl capsenseControl;
QuackControl quackControl;

void setup() {
  Serial.begin(9600);
  DEBUG_PRINT("Begin Setup");
  Serial.println("fuck arduino");
  init_uber_state_idle();
  DEBUG_PRINT("Setup Complete");
}

void loop() {
  //update_rgb_idle();
  //delay(50);
  //test_ledbar();
  //update_uber_state_idle();
  
  if(curState == STATE_IDLE)
  {
    update_uber_state_idle();
  }
  else if(curState == STATE_AGITATED)
  {
    update_uber_state_agitated();
  }
  else if(curState == STATE_EXCITED)
  {
    update_uber_state_excited();
  }
  else if(curState == STATE_SLEEPY)
  {
    update_uber_state_sleepy();
  }
  else if(curState == STATE_PATROL)
  {
    update_uber_state_patrol();
  }
  else
  {
    DEBUG_PRINT("Incorrect or no state chosen");
  }
  updateCapSense();
}

void tests() {
  //laserControl.test_laser();
  delay(500);
  quackControl.test_quack();
  delay(500);
  rgbStrip.test_rgb();
  delay(500);
  servoControl.test_servo();
  delay(500);
  ledBar.test_ledbar();
  delay(500);
  capsenseControl.test_capsense();
  delay(500);
  Serial.println("Tests completed");
}

 /*
  setServoPosition(140, 10);
  playQuack();
  delay(1000);
  setServoPosition(0, 10);
  playQuack();
  delay(1000);
  
  
  //capsense checking:
  temp = checkCapSense();
  for(int i = 0; i < 5; i ++)
  {
    Serial.print(temp.charAt(i));
  }
  */
  
//exampleArray {RGBState, LEDBarState, CapSenseState, QuackState, ServoState}

void init_uber_state_idle()
{
  curState = STATE_IDLE;
  rgbStrip.init_rgb_fade(RGB_BLUE, 10, 255, 1, 1);
  ledBar.init_ledbar_chase(1700);
  laserControl.init_laser_idle();
  quackControl.init_quack_idle();
}

void update_uber_state_idle()
{
  rgbStrip.update_rgb_fade();
  ledBar.update_ledbar_chase();
  laserControl.update_laser_idle();
  quackControl.update_quack_idle();
  //delay();
}




void init_uber_state_agitated()
{
  uberStateStart = millis();
  curState = STATE_AGITATED;
  DEBUG_PRINT("Initialize Agitated");
  rgbStrip.init_rgb_flash(RGB_RED,255,200);
  ledBar.init_ledbar_chase(5);
  laserControl.init_laser_flash(1000);
  quackControl.init_quack_on_delay(1000);
  servoControl.init_servo_agitated(0, 100, 5, 1000);
}

void update_uber_state_agitated()
{
  DEBUG_PRINT(millis()-uberStateStart);
  if(millis()-uberStateStart < AGITATED_TIME)
  {
    DEBUG_PRINT("Update Agitated");
    rgbStrip.update_rgb_flash();
    ledBar.update_ledbar_chase();
    laserControl.update_laser_flash();
    quackControl.update_quack_on_delay();
    servoControl.update_servo_agitated();
    //servoControl.setServoPosition(90, 1);
    //rgbStrip.setRGBStripColor(0,200,0);
  }
  else
  {
    init_uber_state_patrol();
  }
}






#define PATROL_TIME 10000


void init_uber_state_patrol()
{
  uberStateStart = millis();
  curState = STATE_PATROL;
  DEBUG_PRINT("Initialize Patrol");
  rgbStrip.init_rgb_flash(RGB_GREEN,200,1200);
  ledBar.init_ledbar_chase(500);
  laserControl.init_laser_flash(100);
  quackControl.init_quack_on_delay(1000);
}

void update_uber_state_patrol()
{
  if(millis()-uberStateStart < PATROL_TIME)
  {
    DEBUG_PRINT("Update Patrol");
    rgbStrip.update_rgb_flash();
    ledBar.update_ledbar_chase();
    laserControl.update_laser_flash();
    quackControl.update_quack_on_delay();
  }
  else
  {
    init_uber_state_idle();
  }
}








void init_uber_state_excited()
{
  curState = STATE_EXCITED;
  
}

void update_uber_state_excited()
{
  
  
}









void init_uber_state_sleepy()
{
  curState = STATE_SLEEPY;
  
}

void update_uber_state_sleepy()
{
  
  
}

String tempcs;

void updateCapSense()
{
  tempcs = capsenseControl.checkCapSense();
  DEBUG_PRINT("capsense: "+tempcs);
  if(tempcs == "00000"||curState == STATE_AGITATED)
  {
    
  }
  else
  {
    init_uber_state_agitated();
  }
}










// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
    if (quackControl.sample >= sounddata_length) {
        if (quackControl.sample == sounddata_length + quackControl.lastSample) {
            quackControl.stopPlayback();
        }
        else {
            if(SPEAKER_PIN==11){
                // Ramp down to zero to reduce the click at the end of playback.
                OCR2A = sounddata_length + quackControl.lastSample - quackControl.sample;
            } else {
                OCR2B = sounddata_length + quackControl.lastSample - quackControl.sample;                
            }
        }
    }
    else {
        if(SPEAKER_PIN==11){
            OCR2A = pgm_read_byte(&sounddata_data[quackControl.sample]);
        } else {
            OCR2B = pgm_read_byte(&sounddata_data[quackControl.sample]);            
        }
    }

    ++quackControl.sample;
}


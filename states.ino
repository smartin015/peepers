#define UBER_STATE_IDLE 1
#define UBER_STATE_AGITATED 2
#define UBER_STATE_PATROL 3
#define UBER_STATE_EXCITED 4
#define UBER_STATE_SLEEPY 5

//exampleArray {RGBState, LEDBarState, CapSenseState, QuackState, ServoState}
int idle[] = {};

void init_uber_state_idle()
{
  init_rgb_fade(1, 2, 130, 10);
  init_ledbar_chase(1700);
  init_laser_idle();
}

void update_uber_state_idle()
{
  update_rgb_fade();
  update_ledbar_chase();
  update_laser_idle();
  //delay();
}




void init_uber_state_agitated()
{
  init_rgb_flash(0,255,100);
  init_ledbar_chase(50);
  init_laser_flash(1000);
}

void update_uber_state_agitated()
{
  update_rgb_flash();
  update_ledbar_chase();
  update_laser_flash();
}





void init_uber_state_patrol()
{
  
}

void init_uber_state_excited()
{
  
}

void init_uber_state_sleepy()
{
  
}

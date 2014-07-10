#include "commands.h"

#define SPEAKER_PIN 3
#define RGB_PIN 9
#define LASER_PIN 2

#define RF_ADDRESS "serv1"

String temp;

void setup() {
  Serial.begin(9600);

  setup_RF(RF_ADDRESS);
  setup_QUACK(SPEAKER_PIN);
  setup_RGB();
  setup_LASER(LASER_PIN);
  setup_SERVO(10);
  setup_CAPSENSE(3000);
  setup_LEDBAR(4, 6, 5, A6, A7);
  //playQuack();
  tests();
}

void loop() {
  //rf_check_for_cmd();
  
}

void tests() {
  test_laser();
  delay(500);
  test_quack();
  delay(500);
  test_rgb();
  delay(500);
  test_servo();
  delay(500);
  test_ledbar();
  delay(500);
  test_capsense();
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

#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>
#include <stdint.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
    
#include "sounddata.h"
#include "commands.h"

//rgb strip number and pin
#define NUM_LEDS 4
#define RGB_PIN 9

//LED Bar pins
#define LATCH_PIN 4
#define CLOCK_PIN 6
#define DATA_PIN 5

//speaker pin
#define SPEAKER_PIN 3

//laser pin
#define LASER_PIN 2

#define SERVO_PIN 10

//rf address
#define RF_ADDRESS "serv1"

//quack sample rate
#define SAMPLE_RATE 8000


#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

#define RGB_STRIP


typedef enum State{  // <-- the us of typedef is optional
  STATE_IDLE,
  STATE_AGITATED,
  STATE_EXCITED,
  STATE_SLEEPY,
  STATE_PATROL
};

State curState = STATE_IDLE;

typedef enum RGBColor{
  RGB_RED,
  RGB_GREEN,
  RGB_BLUE
};


unsigned long uberStateStart;
#define AGITATED_TIME 10000

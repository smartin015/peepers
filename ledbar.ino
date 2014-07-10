
//Pin connected to ST_CP of 74HC595
int latchPin = 4;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
//Pin connected to DS of 74HC595
int dataPin = 5;
int derpPin1;
int derpPin2;


void setup_LEDBAR(int latch, int clock, int data, int derp1, int derp2) {
  //set pins to output so you can control the shift register
  derpPin1 = derp1;
  derpPin2 = derp2;
  latchPin = latch;
  clockPin = clock;
  dataPin = data;
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //pinMode(derpPin1, OUTPUT);
  //pinMode(derpPin2, OUTPUT);
  
  setLEDBarInt(0);
}


void setLEDBar(int a, int b, int c, int d, int e, int f, int g, int h)
{
  int numberToDisplay = 0;
  
  if(a == 1) {
    numberToDisplay += 1;
  }
  if(b == 1) {
    numberToDisplay += 2;
  }
  if(c == 1) {
    numberToDisplay += 4;
  }
  if(d == 1) {
    numberToDisplay += 8;
  }
  if(e == 1) {
    numberToDisplay += 16;
  }
  if(f == 1) {
    numberToDisplay += 32;
  }
  if(g == 1) {
    numberToDisplay += 64;
  }
  if(h == 1) {
    numberToDisplay += 128;
  }
  shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
  digitalWrite(latchPin, HIGH); 
  digitalWrite(latchPin, LOW);
  /*
  if(i == 1) {
    digitalWrite(derpPin1, HIGH); 
  }
  if(j == 1) {
    digitalWrite(derpPin2, HIGH); 
  }
  */
}

void setLEDBarInt(int displayNum)
{
  shiftOut(dataPin, clockPin, MSBFIRST, displayNum);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW); 
}

void clearLEDBar()
{
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, HIGH); 
  digitalWrite(latchPin, LOW);
}

void test_ledbar()
{
  Serial.println("LED Bar chaser");
  for(int i = 0; i < 8; i++) 
  {
    clearLEDBar();
    setLEDBarInt(1<<i);
    delay(250);
  }
}
  
  /*
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(500);
  }
  */


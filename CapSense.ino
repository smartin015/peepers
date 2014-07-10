#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   wire1 = CapacitiveSensor(A3,A0);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   wire2 = CapacitiveSensor(A3,A1);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   wire3 = CapacitiveSensor(A3,A2);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
CapacitiveSensor   wire4 = CapacitiveSensor(A3,A4);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   wire5 = CapacitiveSensor(A3,A5);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
String output = "";

void setup_CAPSENSE(int timeOut)                    
{
  
  wire1.set_actual_CS_Timeout_Millis(timeOut);
  wire2.set_actual_CS_Timeout_Millis(timeOut);
  wire3.set_actual_CS_Timeout_Millis(timeOut);
  wire4.set_actual_CS_Timeout_Millis(timeOut);
  wire5.set_actual_CS_Timeout_Millis(timeOut);
  
  wire1.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
 
}
//"00000" 
//"10101"
String checkCapSense()
{
  long start = millis();
  output = "";
  long mySensVals[] = {6, 6, 6, 6, 6};
  
  
  mySensVals[0] =  wire1.capacitiveSensor(30);
  mySensVals[1] =  wire2.capacitiveSensor(30);
  mySensVals[2] =  wire3.capacitiveSensor(30);
  mySensVals[3] =  wire4.capacitiveSensor(30);
  mySensVals[4] =  wire5.capacitiveSensor(30);
  
  //Serial.print(millis() - start);        // check on performance in milliseconds
  //Serial.print("\t");                    // tab character for debug windown spacing
  
  for(int i = 0; i < 5; i ++)
  {
    if(mySensVals[i] == -2) {
      output += 1;
    }
    else {
      output += 0;
    }
  }
  
  return output;
}

void test_capsense()
{
  String temp = "000000";
  for(int i = 0; i < 5; i ++)
  {
    Serial.println("Please touch a wire");
    while(temp.charAt(i) == '0') {
      temp = checkCapSense();
      
    }
  }
}

/*
void loop()                    
{
    
    
  long start = millis();
  long total1 =  wire1.capacitiveSensor(30);
  long total2 =  wire2.capacitiveSensor(30);
  long total3 =  wire3.capacitiveSensor(30);
  long total4 =  wire4.capacitiveSensor(30);
  long total5 =  wire5.capacitiveSensor(30);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total2);                  // print sensor output 2
  Serial.print("\t");
  Serial.print(total3);                     // print sensor output 2
  Serial.print("\t");
  Serial.print(total4);                     // print sensor output 2
  Serial.print("\t");
  Serial.println(total5);                     // print sensor output 2

  delay(10);                             // arbitrary delay to limit data to serial port 
}*/

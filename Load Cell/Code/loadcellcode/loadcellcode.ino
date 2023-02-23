#include "HX711.h"
HX711 loadcell;


float  val = 0; 
float analval = 0; 
int DOUTpin = 3; 
int SCKpin = 2; 

const long LOADCELL_OFFSET = 2;
const long LOADCELL_DIVIDER = 2;
char buf[50]; 

void setup(){


  loadcell.begin(DOUTpin, SCKpin);
  Serial.begin(38400);
  pinMode(DOUTpin, INPUT); 
//loadcell.set_scale(LOADCELL_DIVIDER);

 loadcell.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  loadcell.tare();    
}

void loop(){
 val = digitalRead(DOUTpin); 
 analval = analogRead(DOUTpin);
 Serial.print("Digital Val Reading"); 
 Serial.println( val); 
 Serial.print("Analog Val Reading "); 
 Serial.println(analval); 
 if (loadcell.wait_ready_timeout(1000)) {
    long reading = loadcell.get_units(10);
  
  
    sprintf(buf,"%lu",reading); 
    Serial.print("Weight: ");
    Serial.println(reading);

    int intReading = readBinaryString(buf);
    Serial.print("weight2:"); 
    Serial.println(intReading); 
       Serial.print("loadcell reading: " );
  Serial.println(loadcell.read());   
} else {
    Serial.println("HX711 not found.");
}
// Serial.print("read average: \t\t");
//  Serial.println(loadcell.read_average(20));
//
//   Serial.print("read: \t\t");
//  Serial.println(loadcell.read());       
 
  loadcell.power_down();             // put the ADC in sleep mode
  delay(5000);
  loadcell.power_up();

}

int readBinaryString(char *s) {
  int result = 0;
  while(*s) {
    result <<= 1;
    if(*s++ == '1') result |= 1;
  }
  return result;
}

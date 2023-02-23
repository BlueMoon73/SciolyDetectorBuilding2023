#include "HX711.h"
HX711 loadcell;


float  val = 0; 
float analval = 0; 
int DOUTpin = 3; 
int SCKpin = 2; 

const long LOADCELL_OFFSET = 50682624;
const long LOADCELL_DIVIDER = 5895655;


void setup(){


  loadcell.begin(DOUTpin, SCKpin);
  Serial.begin(9600);
  pinMode(DOUTpin, INPUT); 
loadcell.set_scale(LOADCELL_DIVIDER);
loadcell.set_offset(LOADCELL_OFFSET);
}

void loop(){
 val = digitalRead(DOUTpin); 
 analval = analogRead(DOUTpin);
 Serial.print("Digital Val Reading"); 
 Serial.println( val); 
 Serial.print("Analog Val Reading"); 
 Serial.println(analval); 
 // 4. Acquire reading
 Serial.print("Weight: ");
 Serial.println(loadcell.get_units(10), 2);
 delay(1000);

}

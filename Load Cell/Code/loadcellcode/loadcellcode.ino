
// importing the HX711 library 
#include "HX711.h"

// creates a HX771 object 
HX711 loadcell;


float  val = 0; 
float analval = 0; 
 int DOUTpin = 3; 
 int SCKpin = 2; 


//const long LOADCELL_OFFSET = 2;
//const long LOADCELL_DIVIDER = 2000;
char buf[50]; 
char otherBuf[50]; 


 // function to run once at the start of the code 
void setup(){
Serial.begin(9600);
loadcell.begin(DOUTpin, SCKpin);
loadcell.set_gain(32); 
 delay(6000); 
 
 
 
// pinMode(DOUTpin, INPUT); 
                  // this value is obtained by calibrating the scale with known weights; see the README for details
Serial.print("get units: \t\t");
  Serial.println(loadcell.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
            // by the SCALE parameter (not set yet)  
//             loadcell.set_scale(20971.f); 
  loadcell.set_scale();    
            
 loadcell.tare();    
 Serial.println("tared"); 

Serial.println(loadcell.get_offset()); 
  Serial.println(loadcell.get_scale()); 
  
 
}

void loop(){
  delay(1000); 
  
if (loadcell.wait_ready_timeout(2000)) {
    long singleRead = loadcell.get_units(); 
    long avgRead = loadcell.get_units(10);
  Serial.print("one reading:\t");
  Serial.print(singleRead, 1);
  Serial.print("\t| average:\t");
  Serial.println(avgRead, 1);
}
//   Serial.println(loadcell.get_units(10));

// val = digitalRead(DOUTpin); 
// analval = analogRead(DOUTpin);
// Serial.print("Digital Val Reading"); 
// Serial.println( val); 
// Serial.print("Analog Val Reading "); 
// Serial.println(analval); 
// if (loadcell.wait_ready_timeout(2000)) {
//    long unitsReading = loadcell.get_units(100);
////    long readAvg = loadcell.read();
////    double valueReading = loadcell.get_value(10); 
//  
////    sprintf(buf,"%lu",unitsReading); 
//    Serial.print("get units: ");
//    Serial.println(unitsReading);
////
//    int intReading = readBinaryString(buf);
//    Serial.print("Units but not binary:"); 
//    Serial.println(intReading); 
//   
//    Serial.print("loadcell reading: " );
//    Serial.println(readAvg);  
//    Serial.println(loadcell.read_average(20));
//    
//     sprintf(otherBuf, "%6ld", readAvg) ; 
//    Serial.print("formatted?:"); 
//    Serial.println(otherBuf); 
//   
//    Serial.print("loadcell get value : " );
//    Serial.println(valueReading);   

//    
//}
//else {
//    Serial.println("HX711 not found.");
//}
//// Serial.print("read average: \t\t");
////  Serial.println(loadcell.read_average(20));
////
//   Serial.println("=================");
////  Serial.println(loadcell.read());       
// 
  loadcell.power_down();             // put the ADC in sleep mode
  delay(2000);

  loadcell.power_up();

}

//int readBinaryString(char *s ) {
//  int result = 0;
//  while(*s) {
//    result <<= 1;
//    if(*s++ == '1') result |= 1;
//  }
//  return result;
//}


// importing the HX711 library 
#include "HX711.h"

// creates a HX771 object 
HX711 loadcell;

// declaring variables 
float digitalVal = 0; 
float analogVal = 0; 
int DOUTpin = 3; 
int SCKpin = 2; 
char readingString[50]; 


// loadcell 
const long LOADCELL_OFFSET = 2;
const long LOADCELL_DIVIDER = 2;


 // function to run once at the start of the code 
void setup(){


// initializes loadcell with pins declared before 
  loadcell.begin(DOUTpin, SCKpin);
 
// initliazes serial monitor at 38400 baud rate 
 Serial.begin(38400);
  pinMode(DOUTpin, INPUT); 


// set the scale and it's values 
  loadcell.set_scale(2280.f);                      
  loadcell.tare();    
}

void loop(){
    
 // reading the values from the DOUTpin on HX711
 digitalVal = digitalRead(DOUTpin); 
 analogVal = analogRead(DOUTpin);
 
 // print the analog and digital values 
 Serial.print("Digital Val Reading"); 
 Serial.println(digitalVal); 
 Serial.print("Analog Val Reading "); 
 Serial.println(analval); 
 
 // set a maximum timeout time, of 1 second 
 if (loadcell.wait_ready_timeout(1000)) {
    
    // print the average of 10 readings from the ADC minus tare weight 
    long reading = loadcell.get_units(10);
    // this reading is a binary reaidng 
  
    // convert the reading value (which is a long), into a string and stores it in the readingString variable 
    sprintf(readingString,"%lu",reading); 
    
    // prints the reaidng value (the binary)
    Serial.print("binary reading: ");
    Serial.println(reading);

    // converting the binary value stored as a string, into a integer. 
    int intReading = readBinaryString(readingString);
    
    // print out the integer readings, and the raw loadcell reading 
    Serial.print("integer reading:"); 
    Serial.println(intReading); 
    Serial.print("loadcell reading: " );
    Serial.println(loadcell.read());   
} 

else { 
    Serial.println("HX711 not found.");
}

  // put the ADC to sleep and turn it back on 
  loadcell.power_down();             
  delay(5000);
  loadcell.power_up();

}


// function that returns a integer 
// purpose of the function is to read a string, that represents a number in binary
// it returns the decimal value of it 

int readBinaryString(char *s) {
  int result = 0; 
  while(*s) {
    result <<= 1;
    if(*s++ == '1') result |= 1;
  }
  
  // returns the result 
  return result;
}

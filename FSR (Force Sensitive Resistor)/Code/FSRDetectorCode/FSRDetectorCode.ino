int redLED = 6;
int greenLED = 5; 
int blueLED = 3;
int FSRpin = 7; 
int fsrReading;   
int fsrMVoltage; 
float lowRange = 400; 
float highRange = 700; 
float fsrVoltage; 
float fsrMass; 
float lowThreshold = 50; 
float highThreshold = 900; 
// setup function that runs once at the start of the code
void setup() { 
  
  // initialize the digital pin as an output.
    Serial.begin(9600); 

  // declare LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT); 
  pinMode(blueLED, OUTPUT);
}

// loop function that runs repeatedly
void loop() {

//   gets the fsr reading (0-1023)
  fsrReading = analogRead(A1); 
  Serial.println("=====================");   
  Serial.print("Raw Reading:: ") ;
  Serial.println(fsrReading);   
  
//converting the fsr reading into millivolts  and printing to serial console 
  fsrMVoltage = map(fsrReading, 0, 1023, 0, 5000);
  fsrVoltage = fsrMVoltage / 1000.000; 
  Serial.print("Voltage reading in ");
  Serial.println(fsrVoltage, 4);  
  Serial.print("Predicted Mass:"); 
  fsrMass = predictMass(fsrVoltage);
  if (fsrMass > 1000) { 
    fsrMass = 990;
  }
  Serial.println(fsrMass); 

  
//  conditionals for determining LEDS to turn on.  
  if (fsrMass < lowThreshold || fsrMass > highThreshold){
    turnOffAll();
  }
 else if (fsrMass < lowRange){
    Serial.print("In low range ");
   turnOffAll();
  digitalWrite(redLED, HIGH) ;
  }
  else if (fsrMass < highRange){
    Serial.print("In mid range ");
  turnOffAll();
  digitalWrite(greenLED, HIGH);
  }
  else {
    Serial.print("In high range in ");
    turnOffAll();
    digitalWrite(blueLED, HIGH); 
  }

    delay(10000);

}

//function to turn off LED
void turnOffAll () { 
  digitalWrite(redLED, LOW);  
  digitalWrite(greenLED, LOW); 
  digitalWrite(blueLED, LOW); 
}

// return predicted mass based on voltage 
float predictMass(float voltage) {

  // formulas to convert voltage into grams, depending on the range of the voltage 
if (voltage < 0.01) { return 35;} 

else if (voltage < 1.4) {  return pow(10, (0.29904306*voltage + 1.61632775)); }

else if (voltage < 3.3) {return pow(10, (0.23089355*voltage + 1.61717848)); }

else if (voltage < 4.2) {return pow(10, (0.33579583*voltage + 1.28475486)) ; }

else if (voltage < 4.5) {return pow(10, (0.712250 * voltage - 0.36356125)) +70; } 

else {return pow(10, (1.50489089*voltage -3.90820165));}

}

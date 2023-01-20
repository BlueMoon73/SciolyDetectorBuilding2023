 

int redLED = 13;
int greenLED = 12; 
int blueLED = 11;
int FSRpin = 7; 
int fsrReading; 
int fsrMVoltage; 
int lowRange = 300; 
int highRange = 500; 
float fsrVoltage; 

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

  
//  conditionals for determining LEDS to turn on.  
  if (fsrReading < lowRange){
   turnOffAll();
  turnOnRed() ;
  }
  else if (fsrReading > lowRange && fsrReading < highRange){
  turnOffAll();
  turnOnGreen();
  }
  else if (fsrReading > highRange) {
    turnOffAll();
    turnOnBlue; 
  }
  
  delay(1000); 

  
  
  
  //converting the fsr reading into millivolts  and printing 
 
  fsrMVoltage = map(fsrReading, 0, 1023, 0, 5000);
  fsrVoltage = fsrMVoltage / 1000.000; 
  Serial.print("Voltage reading in ");
  Serial.println(fsrVoltage);  
  
  
}

void turnOnRed (){
  digitalWrite(redLED, HIGH);
}
void turnOnGreen (){
  digitalWrite(greenLED, HIGH);
}
void turnOnBlue (){
  digitalWrite(blueLED, HIGH);
}

void turnOffAll () { 
  digitalWrite(redLED, LOW); 
  digitalWrite(greenLED, LOW); 
  digitalWrite(blueLED, LOW); 
}
     

 

int redLED = 13;
int greenLED = 12; 
int blueLED = 11;
int FSRpin = 7; 
int fsrReading; 
int fsrMVoltage; 
int lowRange = 300; 
int highRange = 500; 
float fsrVoltage; 
int sum; 
int loopNum; 
int fsrAvgReading; 

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
  sum = 0 ;
  loopNum = 10; 
//  fsrReading = analogRead(A1); 

  for (int i=0; i<loopNum; i++){
    fsrReading = analogRead(A1); 
    sum += fsrReading ;
  }

  fsrAvgReading = sum/loopNum;
  Serial.println("=====================\n=====================");   
  Serial.print("Raw Reading: ") ;
  Serial.println(fsrAvgReading);   

  
//  conditionals for determining LEDS to turn on.  
  if (fsrReading < lowRange){
   turnOffAll();
  turnOnRed() ;
  }
  else if (fsrReading > lowRange && fsrReading < highRange){
  turnOffAll();
  turnOnGreen();
  }
  else {
    turnOffAll();
    turnOnBlue; 
  }

  
  
  
  //converting the fsr reading into millivolts  and printing 
 
  fsrMVoltage = map(fsrAvgReading, 0, 1023, 0, 5000);
  fsrVoltage = fsrMVoltage / 1000.000; 
  Serial.print("Voltage reading in ");
  Serial.println(fsrVoltage, 4);  
  Serial.print("Predicted Mass:"); 
  Serial.println(predictMass(fsrVoltage)); 
  delay(1500);
  
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

float predictMass(float voltage) {

//  return (pow(log(a * voltage * 1000), d))/b;
return (pow(10, (0.43931823*voltage + 1.01804087))); 

//return (pow(2.718, (2.254*voltage)-.2254)-1)/0.38;
}
     

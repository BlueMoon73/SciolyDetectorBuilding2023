float  val = 0; 
float analval = 0; 
int DOUT = 3; 
int SCKpin = 2; 
void setup(){

  Serial.begin(9600);
  pinMode(DOUT, INPUT); 

}

void loop(){
 val = digitalRead(DOUT); 
 analval = analogRead(DOUT);
 Serial.println( val); 
 Serial.println(analval); 
 delay(1000);

}

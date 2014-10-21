//Inputs
byte m_clear = 5;    //Master Clear button
byte m_rec = 6;      //Master Record
byte m_backout1 = 8; //Backout for Channel 1
byte m_morse1 = 10;  //Input for Channel 1
byte m_backout2 = 11;//Backout for Channel 2
byte m_morse2  = 13; //Input for Channel 2

byte m_metronome = A0;  //Analog input for Metronome Speed

//Outputs
byte m_metronome_led = 7;  //Metronome Blinking
byte m_morse_led1 = 9;     // morse 1
byte m_morse_led2 = 12 ;   // morse 2

//Variables

int sensorValue = 0;

void setup() {
  //Setting up Pins
  pinMode(m_clear,INPUT);
  pinMode(m_rec,INPUT);
  pinMode(m_backout1,INPUT);
  pinMode(m_morse1,INPUT);
  pinMode(m_backout2,INPUT);
  pinMode(m_morse2,INPUT);
  
  pinMode(m_metronome_led, OUTPUT);
  pinMode(m_morse_led1, OUTPUT);
  pinMode(m_morse_led2, OUTPUT);
 
}
void loop() {

  //Testing Potentiometer and Metronome Led
  sensorValue = analogRead(m_metronome);    
  // turn the ledPin on
  digitalWrite(m_metronome_led, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);          
  // turn the ledPin off:        
  digitalWrite(m_metronome_led, LOW);  
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
  
  //Testing morse button and LED (remember delays from previous potentiometer
  if(digitalRead(m_morse1) == LOW){
    digitalWrite(m_morse_led1, HIGH);
  }
  else{
    digitalWrite(m_morse_led1, LOW);
  }
  
  if(digitalRead(m_morse2) == LOW){
    digitalWrite(m_morse_led2, HIGH);
  }
  else{
    digitalWrite(m_morse_led2, LOW);
  }
  
  
}

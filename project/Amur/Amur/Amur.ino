// 
// Amur 
//
// Percussive looper w/ capacitive input and solenoid outputs
// Developed with [embedXcode](http://embedXcode.weebly.com)
// 
// Author	 	Hiron Roy
// 				Hiron Roy
//
// Date			10/21/14 9:13 PM
// Version		<#version#>
// 
// Copyright	© Hiron Roy, 2014
// License		<#license#>
//
// See			ReadMe.txt for references
//

// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

// Include application, user and local libraries
#include "tBeat.h"
#include "Conductor.h"
#include "AmurIO.h"
#include "Metronome.h"

// Prototypes

//Inputs
//byte m_clear = 5;    //Master Clear button
//byte m_rec = 6;      //Master Record
//byte m_backout1 = 8; //Backout for Channel 1
//byte m_morse1 = 10;  //Input for Channel 1
//byte m_backout2 = 11;//Backout for Channel 2
//byte m_morse2  = 13; //Input for Channel 2
//
//byte m_metronome = A0;  //Analog input for Metronome Speed
//
////Outputs
//byte m_metronome_led = 7;  //Metronome Blinking
//byte m_morse_led1 = 9;     // morse 1
//byte m_morse_led2 = 12 ;   // morse 2


void runInterval();

void setup() {
    Serial.begin(9600);      // open the serial port at 9600 bps:

    tBeat.init();
    
    tBeat.newHook(amurIO.sampleInterval, runInterval);
    
    tBeat.start();


    //Setting up Pins
//    pinMode(m_clear,INPUT);
//    pinMode(m_rec,INPUT);
//    pinMode(m_backout1,INPUT);
//    pinMode(m_morse1,INPUT);
//    pinMode(m_backout2,INPUT);
//    pinMode(m_morse2,INPUT);
//    
//    pinMode(m_metronome_led, OUTPUT);
//    pinMode(m_morse_led1, OUTPUT);
//    pinMode(m_morse_led2, OUTPUT);
    
}

void runInterval(){
    amurMetronomeHandleInterval();
}

void loop() {
    
    tBeat.exec();

    
//    //Testing Potentiometer and Metronome Led
//    sensorValue = analogRead(m_metronome);
//    // turn the ledPin on
//    digitalWrite(m_metronome_led, HIGH);
//    // stop the program for <sensorValue> milliseconds:
//    delay(sensorValue);
//    // turn the ledPin off:
//    digitalWrite(m_metronome_led, LOW);
//    // stop the program for for <sensorValue> milliseconds:
//    delay(sensorValue);
    
    //Testing morse button and LED (remember delays from previous potentiometer
//    if(digitalRead(m_morse1) == LOW){
//        digitalWrite(m_morse_led1, HIGH);
//    }
//    else{
//        digitalWrite(m_morse_led1, LOW);
//    }
//    
//    if(digitalRead(m_morse2) == LOW){
//        digitalWrite(m_morse_led2, HIGH);
//    }
//    else{
//        digitalWrite(m_morse_led2, LOW);
//    }
    
    
}


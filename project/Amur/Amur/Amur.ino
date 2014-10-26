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
#include "StandardCplusplus.h"

#include "AdafruitCapTouch.h"
#include "tBeat.h"
#include "AmurIO.h"
#include "Metronome.h"
#include "Timeline.h"
#include "Hitter.h"

// Prototypes

//Inputs
//byte m_clear = 5;    //Master Clear button
//byte m_rec = 6;      //Master Record
//byte m_backout1 = 8; //Backout for Channel 1
//byte m_backout2 = 11;//Backout for Channel 2


Hitter hitter1;
//Hitter hitter2;

void runInterval();
void runHitter1();
//void runHitter2();
void printRAM();

int freeRam ()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


void setup() {
    Serial.begin(9600);      // open the serial port at 9600 bps:
    touchDriver.begin();
    //hitters init
    
    // duration of hit (ms), input pin, output pin
    hitter1.begin(80, 80, 8, 9);
//    hitter2.begin(100, 13, 12);

    tBeat.init();
    
    //All of the actuators get triggered at the sample interval
    tBeat.newHook(amurIO.sampleInterval, runInterval);
    tBeat.newHook(amurIO.sampleInterval, runHitter1);
//    tBeat.newHook(amurIO.sampleInterval, runHitter2);
    
//    tBeat.newHook(5000, printRAM);


    tBeat.start();
    
}

void runInterval(){
    amurMetronomeHandleInterval();
    timeline.handleInterval();
}
void runHitter1(){
    hitter1.handleInterval();
}
//void runHitter2(){
//    hitter2.handleInterval();
//}
void printRAM(){
    Serial.println("FREE RAM:");
    Serial.println(freeRam());
}

void loop() {
    tBeat.exec();
}


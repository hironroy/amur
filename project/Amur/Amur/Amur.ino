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


// Include application, user and local libraries
#include <Wire.h>
#include "StandardCplusplus.h"
#include "Adafruit_MPR121.h"
#include "tBeat.h"

#include "AdafruitCapTouch.h"
#include "AmurIO.h"
#include "Metronome.h"
#include "Timeline.h"
#include "Recorder.h"
#include "Hitter.h"

Hitter hitter1;
Hitter hitter2;
Hitter hitter3;
Hitter hitter4;

void runInterval();
void runHitters();
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
    
    // TODO: Set Cap Pin Assignments
    // duration of hit (ms), input (CAP) pin, output pin
    hitter1.begin(80, 80, 3, 9);
    hitter2.begin(80, 80, 4, 10);
    hitter3.begin(80, 80, 5, 11);
    hitter4.begin(80, 80, 6, 12);

//    hitter1.begin(80, 80, 5, 11);
//    hitter1.begin(80, 80, 6, 12);

//    hitter2.begin(100, 13, 12);

    tBeat.init();
    
    //All of the actuators get triggered at the sample interval
    tBeat.newHook(amurIO.sampleInterval, runInterval);
    tBeat.newHook(amurIO.sampleInterval, runHitters);
    
//    tBeat.newHook(5000, printRAM);

    tBeat.start();
    
}

void runInterval(){
    amurMetronomeHandleInterval();
    timeline.handleInterval();
}
void runHitters(){
    hitter1.handleInterval();
    hitter2.handleInterval();
    hitter3.handleInterval();
    hitter4.handleInterval();
}

void printRAM(){
    Serial.println("FREE RAM:");
    Serial.println(freeRam());
}

void loop() {
    tBeat.exec();
}


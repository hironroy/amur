//
//  AmurIO.cpp
//  Amur
//
//  Created by Hiron Roy on 10/22/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "AmurIO.h"

AmurIO amurIO;
void amurBlinkMetronome();
void amurStopBlinkMetronome();

AmurIO::AmurIO(){
    m_metronome = A0;
    m_metronome_led = 8;
    pinMode(m_metronome_led, OUTPUT);

    //say that the sample interval is 8ms
    sampleInterval = 8;
    debounceDuration = 500;
}

int AmurIO::getTempoPotVal(){
    return analogRead(m_metronome);
}

void AmurIO::metronomeLEDOn(){
    digitalWrite(m_metronome_led, HIGH);
}

void AmurIO::metronomeLEDOff(){
    digitalWrite(m_metronome_led, LOW);
}
void AmurIO::blinkMetronomeLED(){
    amurBlinkMetronome();
}


int AmurIO::readPin(byte pincode){
    return digitalRead(pincode);
}

int AmurIO::readCap(byte pincode){
    return touchDriver.isPinUp(pincode);
}

void AmurIO::pushTrigger(byte pincode){
    digitalWrite(pincode, HIGH);
}
void AmurIO::lowTrigger(byte pincode){
    digitalWrite(pincode, LOW);
}


void amurStopBlinkMetronome(){
    amurIO.metronomeLEDOff();
    tBeat.killHook(20, amurStopBlinkMetronome);
}

void amurBlinkMetronome(){
    amurIO.metronomeLEDOn();
    tBeat.newHook(20, amurStopBlinkMetronome);
}

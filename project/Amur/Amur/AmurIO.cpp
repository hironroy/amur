//
//  AmurIO.cpp
//  Amur
//
//  Created by Hiron Roy on 10/22/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "AmurIO.h"

AmurIO amurIO;

AmurIO::AmurIO(){
    m_metronome = A0;
    m_metronome_led = 7;
    pinMode(m_metronome_led, OUTPUT);

    //say that the sample interval is 8ms
    sampleInterval = 8;
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

//
//  Metronome.cpp
//  Amur
//
//  Created by Hiron Roy on 10/22/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Metronome.h"

//Init with min and max BPM's
Metronome metronome(40, 240);

Metronome::Metronome(int _minBPM, int _maxBPM) {
    maxBPM = _maxBPM;
    minBPM = _minBPM;
    BPMRange = maxBPM - minBPM;
    maxTempoPotVal = 1020;
    isBeatInterval = false;
}

int Metronome::getCurrentDelay(){
    float bpm;
    bpm = getCurrentBPM();
    
    return floor(60 * (1000 / bpm) + 0.5);
}

float Metronome::getCurrentBPM(){
    int tempoPotVal;
    float ratio;
    float minusBPM;

    tempoPotVal = amurIO.getTempoPotVal();
    ratio = (float) tempoPotVal / (float) maxTempoPotVal;
    minusBPM = (float)BPMRange * ratio;
    
    return (float) maxBPM - minusBPM;
}

int msSinceLastBlink = 0;
int lastReadTempoDelay = metronome.getCurrentDelay();


void amurMetronomeHandleInterval(){
    msSinceLastBlink += amurIO.sampleInterval;
    
    metronome.isBeatInterval = false;
    
    int currentDelay = metronome.getCurrentDelay();
    if(msSinceLastBlink > currentDelay){
        //Beat Detected
        amurIO.blinkMetronomeLED();
        metronome.isBeatInterval = true;
        msSinceLastBlink = 0;
    }
    lastReadTempoDelay = currentDelay;
}







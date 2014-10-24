//
//  Hitter.cpp
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Hitter.h"

Hitter::Hitter() {
    //leave blank
}

void Hitter::begin(int _hitDuration, byte _inputPin,  byte _outputPin){
    hitDuration = _hitDuration;
    isDoingHit = false;
    newHit = false;
    outputPin = _outputPin;
    inputPin = _inputPin;
    msSinceLastHit = 0;
    
    pinMode(outputPin, OUTPUT);
    pinMode(inputPin, INPUT);
}

void Hitter::handleInterval(){
    
    if(amurIO.readPin(inputPin) == LOW){
        doHit();
    }
    
    if(newHit){
        //trigger the hit against AmurIO to output pin
        amurIO.pushTrigger(outputPin);
        
        //set is doing hit
        newHit = false;

        msSinceLastHit = 0;
    }
    else if(isDoingHit){

        amurIO.pushTrigger(outputPin);
        
        msSinceLastHit += amurIO.sampleInterval;

        if(msSinceLastHit >= hitDuration){
            isDoingHit = false;
            msSinceLastHit = 0;
            amurIO.lowTrigger(outputPin);
        }
    }
    else{
        amurIO.lowTrigger(outputPin);
    }
}

void Hitter::doHit(){
    if(!isDoingHit){
        newHit = true;
        isDoingHit = true;
    }
}


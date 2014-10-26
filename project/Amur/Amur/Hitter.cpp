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

void Hitter::begin(int _hitDuration, int _reboundDuration, byte _inputPin,  byte _outputPin){
    hitDuration = _hitDuration;
    reboundDuration = _reboundDuration;
    isDoingHit = false;
    newHit = false;
    outputPin = _outputPin;
    inputPin = _inputPin;
    msSinceLastHit = 0;
    
    pinMode(outputPin, OUTPUT);
    pinMode(inputPin, INPUT);
    
    recorder = Recorder();
    recorder.begin();
}

void Hitter::handleInterval(){
    
    //If not currently doing a hit
        //if user inputted hit --
            // do hit
            // if(!recorder.ratioHasHit(ratio) -- recorder.recordHit
        //else if recorder.ratioHasHit(ratio) -- do hit
        //else -- push trigger down & set msSinceHitStarted = 0

    //else //Doing a hit
        // push trigger up
        // increment the the msSinceHitStarted
        // if the msSinceHitStarted is exceeded -- push trigger down & msSinceHitStarted = 0
    
    if(timeline.loopReset){
        recorder.resetLoop();
    }
    
    updateOneHitStatus();
    if(!isDoingHit){
        float currentRatio = timeline.ratioComplete();

        if(userPressing()){
            doHit();
            if(timeline.isLoopPlaying() && !recorder.ratioHasHit(currentRatio)){
                recorder.recordHit(currentRatio);
            }
        }
        else if(timeline.isLoopPlaying() && recorder.ratioHasHit(currentRatio)){
            Serial.println("Recorded Hit Play");
            doHit();
            recorder.moveToNextHit();
        }
    }

    if(timeline.clearLoopTriggered){
        recorder.clearAll();
    }
    
}

// Is user inputting to the hitter?
bool Hitter::userPressing(){
    return amurIO.readCap(inputPin);
}

// Trigger the start of a hit
void Hitter::doHit(){
    amurIO.pushTrigger(outputPin);
    msSinceLastHit += amurIO.sampleInterval;
    isDoingHit = true;
}

//Kicked off every interval
//Check if the solenoid should be up, retracting or down
void Hitter::updateOneHitStatus(){
    if(isDoingHit){
        msSinceLastHit += amurIO.sampleInterval;
        
        if(msSinceLastHit > (hitDuration + reboundDuration)){
            resetOneHit();
        }
        else if(msSinceLastHit > reboundDuration){
            amurIO.lowTrigger(outputPin);
        }
        else{
            amurIO.pushTrigger(outputPin);
        }
    }
}

//Cleanup variables after a hit
void Hitter::resetOneHit(){
    amurIO.lowTrigger(outputPin);
    isDoingHit = false;
    msSinceLastHit = 0;
}

//void Hitter::handleInterval(){
//    
//    if(amurIO.readCap(inputPin)){
//        doHit();
//    }
//    
//    if(newHit || (recorder.intervalHasHit() && !isDoingHit)){
//        Serial.println("Output Hit");
//        actuateHit();
//    }
//    else if(isDoingHit){
//
//        amurIO.pushTrigger(outputPin);
//        
//        msSinceLastHit += amurIO.sampleInterval;
//
//        if(msSinceLastHit >= hitDuration){
//            isDoingHit = false;
//            msSinceLastHit = 0;
//            amurIO.lowTrigger(outputPin);
//        }
//    }
//    else{
//        amurIO.lowTrigger(outputPin);
//    }
//}

//void Hitter::actuateHit(){
//    //trigger the hit against AmurIO to output pin
//    amurIO.pushTrigger(outputPin);
//    //set is doing hit
//    newHit = false;
//    msSinceLastHit = 0;
//}
//
//void Hitter::doHit(){
//    if(!isDoingHit){
//        if(recorder.isRecording()){
//            routeHitToRecorder();
//        }
//        newHit = true;
//        isDoingHit = true;
//    }
//}
//
//void Hitter::routeHitToRecorder(){
//    recorder.recordHit();
//}


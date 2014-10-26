//
//  Timeline.cpp
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Timeline.h"

Timeline timeline(10,11, 9);


Timeline::Timeline(int _startLockPin, int _clearPin, int _bailPin){
    startLockPin = _startLockPin;
    clearPin = _clearPin;
    bailPin = _bailPin;
    
    pinMode(startLockPin, INPUT);
    pinMode(clearPin, INPUT);
    
    timeSinceClearPress = 0;
    timeSinceBailPress = 0;
    timeSinceStartPress = 0;
    
    hasLoop = false;
    loopBeatCount = 0;
    currentBeat = -1;
    loopPercentPlayed = 0.0;
    
    maxLoopLength = 8000;
}

void Timeline::handleInterval(){
    
    if(isSettingLoop){
        timeSinceLoopDefStart += amurIO.sampleInterval;
        if(timeSinceLoopDefStart > maxLoopLength){
            lock();
            timeSinceLoopDefStart = 0;
        }
    }
    
    if(startTriggered()){
        start();
    }
    
    clearLoopTriggered = false;
    if(clearTriggered()){
        clear();
    }
    
    bailLoopTriggered = false;
    if(bailTriggered()){
        Serial.println("Bail Triggered");
        bailLoopTriggered = true;
    }
    
    updateLoop();
    
}


void Timeline::updateLoop(){
    loopReset = false;
    
    //count the beats if setting loop
    if(isSettingLoop && metronome.isBeatInterval){
        loopBeatCount++;
    }
    else if (metronome.isBeatInterval && hasLoop) {
        loopIsPlaying = true;
        
        //update the current beat
        if(currentBeat == loopBeatCount || currentBeat < 0){
            resetLoop();
        }
        currentBeat += 1;

        
    }
    
    if(hasLoop){
        updateLoopPercentage();
    }

}

void Timeline::updateLoopPercentage(){
    //Now we calculate the % complete
    if(loopIsPlaying){
        int loopDuration = metronome.getCurrentDelay() * loopBeatCount;
        float sampleDurationRatio = (float) amurIO.sampleInterval / (float)loopDuration;
        loopPercentPlayed += sampleDurationRatio;
    }
}


void Timeline::resetLoop(){
    //reset the loop
    currentBeat = 0;
    loopPercentPlayed = 0.0;
    loopReset = true;
}

void Timeline::start(){
    if(!isSettingLoop && !hasLoop){
        isSettingLoop = true;
        Serial.println("Start Setting Loop Length");
        timeSinceLoopDefStart = 0;
    }
    else if(isSettingLoop){
        lock();
    }
}

void Timeline::lock(){
    Serial.println("Loop Length Set");
    isSettingLoop = false;
    hasLoop = true;

}

void Timeline::clear(){
    Serial.println("Clear Loop");
    clearLoopTriggered = true;
    hasLoop = false;
    loopBeatCount = 0;
}

float Timeline::ratioComplete(){
    return loopPercentPlayed;
}

bool Timeline::isLoopPlaying(){
    return loopIsPlaying;
}

/**
 Handle Debouncing inputs
 */
bool Timeline::startTriggered(){
    
    if(timeSinceStartPress == 0 && amurIO.readCap(startLockPin)){
        timeSinceStartPress += amurIO.sampleInterval;
        return true;
    }
    else if(timeSinceStartPress >= amurIO.debounceDuration){
        timeSinceStartPress = 0;
        return false;
    }
    else if(timeSinceStartPress > 0){
        timeSinceStartPress += amurIO.sampleInterval;
        return false;
    }
    else{
        return false;
    }
}

bool Timeline::bailTriggered(){
    
    if(timeSinceBailPress == 0 && amurIO.readCap(bailPin)){
        timeSinceBailPress += amurIO.sampleInterval;
        return true;
    }
    else if(timeSinceBailPress >= amurIO.debounceDuration){
        timeSinceBailPress = 0;
        return false;
    }
    else if(timeSinceBailPress > 0){
        timeSinceBailPress += amurIO.sampleInterval;
        return false;
    }
    else{
        return false;
    }
}

bool Timeline::clearTriggered(){
    if(timeSinceClearPress == 0 && amurIO.readCap(clearPin)){
        timeSinceClearPress += amurIO.sampleInterval;
        return true;
    }
    else if(timeSinceClearPress >= amurIO.debounceDuration){
        timeSinceClearPress = 0;
        return false;
    }
    else if(timeSinceClearPress > 0){
        timeSinceClearPress += amurIO.sampleInterval;
        return false;
    }
    else{
        return false;
    }
}

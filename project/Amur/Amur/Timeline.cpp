//
//  Timeline.cpp
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Timeline.h"

Timeline timeline(10,11);


Timeline::Timeline(int _startLockPin, int _clearPin){
    startLockPin = _startLockPin;
    clearPin = _clearPin;
    
    pinMode(startLockPin, INPUT);
    pinMode(clearPin, INPUT);
    
    timeSinceClearPress = 0;
    timeSinceStartPress = 0;
    
    hasLoop = false;
    loopBeatCount = 0;
    currentBeat = -1;
    loopPercentPlayed = 0.0;
}

void Timeline::handleInterval(){
    //IO Related Logic
    if(startTriggered()){
        start();
    }
    
    if(clearTriggered()){
        clear();
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
        double sampleDurationRatio = (double) amurIO.sampleInterval / (double)loopDuration;
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
    }
    else if(isSettingLoop){
        lock();
    }
}

void Timeline::lock(){
    isSettingLoop = false;
    hasLoop = true;

}

void Timeline::clear(){
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

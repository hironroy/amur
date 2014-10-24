//
//  Timeline.cpp
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Timeline.h"

Timeline timeline(6,5);


Timeline::Timeline(int _startLockPin, int _clearPin){
    startLockPin = _startLockPin;
    clearPin = _clearPin;
    
    pinMode(startLockPin, INPUT);
    pinMode(clearPin, INPUT);
    
    timeSinceClearPress = 0;
    timeSinceStartPress = 0;
    
    hasLoop = false;
    loopBeatCount = 0;
}

void Timeline::handleInterval(){
    //IO Related Logic
    if(startTriggered()){
        start();
    }
    
    if(clearTriggered()){
        clear();
    }
    
    //count the beats if setting loop
    if(isSettingLoop && metronome.isBeatInterval){
        loopBeatCount++;
        Serial.println("Loop Beat Count");
        Serial.println(loopBeatCount);
    }
}

void Timeline::start(){
    if(!isSettingLoop && !hasLoop){
        isSettingLoop = true;
        Serial.println("Timeline Start Loop");
    }
    else if(isSettingLoop){
        lock();
    }
}

void Timeline::lock(){
    isSettingLoop = false;
    hasLoop = true;
    Serial.println("Timeline Loop Lock");

}

void Timeline::clear(){
    hasLoop = false;
    loopBeatCount = 0;
    Serial.println("Timeline Clear");
}

float Timeline::ratioComplete(){
    
}

bool Timeline::startTriggered(){
    
    if(timeSinceStartPress == 0 && amurIO.readPin(startLockPin) == LOW){
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
    if(timeSinceClearPress == 0 && amurIO.readPin(clearPin) == LOW){
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

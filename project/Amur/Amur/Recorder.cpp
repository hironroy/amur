//
//  Recorder.cpp
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Recorder.h"

Recorder::Recorder(){

}

void Recorder::begin(){
    currentHitIndex = 0;
    newLoop = false;
    maxNewHits = 50;
    maxLoopHits = 100;
    
    newHits.reserve(maxNewHits);
    hits.reserve(maxLoopHits);

    
}

bool Recorder::isRecording(){
    return timeline.isLoopPlaying();
}

void Recorder::recordHit(float ratio){
    if(newHits.size() <= maxNewHits){
        newHits.push_back(ratio);
    }
}

void Recorder::clearAll(){

    Serial.println("Recorder clear all hits");
    hits.clear();
    newHits.clear();
    
}

void Recorder::resetLoop(){
    currentHitIndex = 0;
    saveNewHits();
}

void Recorder::saveNewHits(){
    //merge hits & newHits, sort the new resultant hits.
    if(!newHits.empty()){
        if(newHits.size() + hits.size() > maxLoopHits){
            hits = newHits;
        }
        else{
            std::vector<float> newMerged(hits.size() + newHits.size());
            std::merge(hits.begin(), hits.end(),newHits.begin(), newHits.end(), newMerged.begin());
            
            hits = newMerged;
            printHits();
        }
        newHits.clear();
    }
}

void Recorder::printHits(){
    Serial.println("Loop Hits");
    for (std::vector<float>::iterator it=hits.begin(); it!=hits.end(); ++it){
        Serial.println(*it);
    }
}

void Recorder::printNewHits(){
    Serial.println("New Hits");
    for (std::vector<float>::iterator it=newHits.begin(); it!=newHits.end(); ++it){
            Serial.println(*it);
    }
}

void Recorder::moveToNextHit(){
    if(currentHitIndex >= (hits.size() - 1)){
        currentHitIndex = -1;
    }
    else{
        currentHitIndex++;
    }
}
bool Recorder::ratioHasHit(float ratio){
    //TODO implement check
    
    if(currentHitIndex >= 0){
        if(!hits.empty()){
            return hits.at(currentHitIndex) < ratio;
        }
    }

    return false;
}
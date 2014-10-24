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
    hits.push_back(0.00);
    hits.push_back(0.50);
    
    currentHitIndex = 0;
    newLoop = false;
    
    Serial.println("Init Recorder");
    Serial.println(hits.size());
}

bool Recorder::isRecording(){
    return timeline.isLoopPlaying();
}

void Recorder::recordHit(){
//    hits.push_back(timeline.ratioComplete());
    //we're actually going to need to sort this and merge in the new hits into the old.
    //also store the backout.
}

bool Recorder::intervalHasHit(){
    if(timeline.isLoopPlaying()){
        double ratio = timeline.ratioComplete();
        
        if(currentHitIndex < 0 && timeline.loopReset){
            currentHitIndex = 0;
        }
        else if(currentHitIndex< 0){
            return false;
        }
        
        if(ratio >= hits[currentHitIndex]){
            
            if(currentHitIndex >= hits.size() - 1){
                currentHitIndex = -1;
            }
            else{
                currentHitIndex = currentHitIndex + 1;
            }
            
            
            return true;
            
        }else{
            return false;
        }
    }
   else{
       return false;
   }
}
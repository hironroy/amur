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
    currentHitIndex = -1;
    newLoop = false;
}

bool Recorder::isRecording(){
    return timeline.isLoopPlaying();
}

void Recorder::recordHit(){
//    hits.push_back(timeline.ratioComplete());
    //we're actually going to need to sort this and merge in the new hits into the old.
    //also store the backout.
    newHits.push_back(timeline.ratioComplete());
}

void Recorder::saveNewHits(){
    //merge hits & newHits, sort the new resultant hits.
    if(!newHits.empty()){
        std::vector<float> newAllHits(hits.size() + newHits.size());
        std::merge(hits.begin(), hits.end(),newHits.begin(), newHits.end(), newAllHits.begin());

//        Serial.println("New Hits");
//        for (std::vector<float>::iterator it=newHits.begin(); it!=newHits.end(); ++it)
//            Serial.println(*it);
//        
//        Serial.println("Old Hits");
//        for (std::vector<float>::iterator it=hits.begin(); it!=hits.end(); ++it)
//            Serial.println(*it);
//        
//        Serial.println("Post Merge");
//        for (std::vector<float>::iterator it=newAllHits.begin(); it!=newAllHits.end(); ++it)
//            Serial.println(*it);

        hits = newAllHits;
        newHits.clear();
    }
}

bool Recorder::intervalHasHit(){
    if(timeline.isLoopPlaying() && !hits.empty()){
        
        float ratio = timeline.ratioComplete();
        
        if(currentHitIndex < 0 && timeline.loopReset){
            currentHitIndex = 0;
            saveNewHits();
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
            
            Serial.println("Trigger Recorded Hit");
            return true;
            
        }else{
            return false;
        }
    }
   else{
       return false;
   }
}
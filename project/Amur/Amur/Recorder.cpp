//
//  Recorder.cpp
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "Recorder.h"

Recorder::Recorder(){
    hits.reserve(400);
}

bool Recorder::isRecording(){
    return timeline.isLoopPlaying();
}

void Recorder::recordHit(){
    hits.push_back(timeline.ratioComplete());
    
    //print out the vectors
    for (unsigned i=0; i<hits.size(); ++i)
    {
        Serial.println(hits[i]);
    }
    
}

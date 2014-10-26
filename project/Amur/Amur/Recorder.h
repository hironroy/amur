//
//  Recorder.h
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Recorder__
#define __Amur__Recorder__

#include "Arduino.h"
#include "StandardCplusplus.h"
#include <vector>
#include "Timeline.h"

class Recorder {
public:
    Recorder();
    void printNewHits();
    void printHits();
    void begin();
    bool isRecording();
    void recordHit(float ratio);
    void bail();
    void clearAll();
    bool ratioHasHit(float ratio);
    void saveNewHits();
    void resetLoop();
    void moveToNextHit();
    unsigned int maxNewHits;
    unsigned int maxLoopHits;
private:
    std::vector<float> hits;
    std::vector<float> newHits;

    int currentHitIndex;
    bool newLoop;
};

#endif /* defined(__Amur__Recorder__) */

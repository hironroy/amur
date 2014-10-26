//
//  Recorder.h
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Recorder__
#define __Amur__Recorder__

#include <iostream>
#include "StandardCplusplus.h"
#include "AmurIO.h"
#include "Timeline.h"

class Recorder {
public:
    Recorder();

    void begin();
    bool isRecording();
    void recordHit();
    bool intervalHasHit();
private:
    std::vector<float> hits;
    std::vector<float> newHits;
    int currentHitIndex;
    bool newLoop;
    void saveNewHits();
};

#endif /* defined(__Amur__Recorder__) */

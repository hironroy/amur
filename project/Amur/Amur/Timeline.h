//
//  Timeline.h
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Timeline__
#define __Amur__Timeline__

#include <iostream>
#include "StandardCplusplus.h"
#include "AmurIO.h"
#include "Metronome.h"

class Timeline{
public:
    Timeline(int _startLockPin, int _clearPin);
    void handleInterval();
    void start();
    void lock();
    void clear();
    float ratioComplete();
    bool startTriggered();
    bool clearTriggered();
private:
    float lastRatioComplete;
    int startLockPin;
    int timeSinceStartPress;
    int clearPin;
    int timeSinceClearPress;
    
};

extern Timeline timeline;

#endif /* defined(__Amur__Timeline__) */
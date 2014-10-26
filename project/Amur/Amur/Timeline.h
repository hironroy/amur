//
//  Timeline.h
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Timeline__
#define __Amur__Timeline__

#include "Arduino.h"
#include "AmurIO.h"
#include "Metronome.h"


class Timeline{
public:
    Timeline(int _startLockPin, int _clearPin, int _bailPin);
    void handleInterval();
    void start();
    void lock();
    void clear();
    float ratioComplete();
    bool startTriggered();
    bool clearTriggered();
    bool bailTriggered();
    bool isLoopPlaying();
    bool loopReset;
    bool clearLoopTriggered;
    bool bailLoopTriggered;

private:
    void startLoopPlay();
    void updateLoop();
    void resetLoop();
    void updateLoopPercentage();
    
    bool loopIsPlaying;
    float lastRatioComplete;
    int startLockPin;
    int timeSinceStartPress;
    int clearPin;
    int timeSinceClearPress;
    
    int bailPin;
    int timeSinceBailPress;
    
    int timeSinceLoopDefStart;
    
    bool isSettingLoop;
    bool hasLoop;
    int loopBeatCount;
    int currentBeat;
    float loopPercentPlayed;
    
    int maxLoopLength;
    
};

extern Timeline timeline;

#endif /* defined(__Amur__Timeline__) */

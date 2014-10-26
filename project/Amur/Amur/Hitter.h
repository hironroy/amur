//
//  Hitter.h
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Hitter__
#define __Amur__Hitter__
#include "Arduino.h"
#include "AmurIO.h"
#include "Timeline.h"
#include "Recorder.h"

class Hitter {
public:
    Hitter();
    void begin(int _hitDuration, int _reboundDuration, byte _inputPin, byte _outputPin);
    void doHit();
    void handleInterval();
private:
    bool isDoingHit;
    int hitDuration;
    int reboundDuration;
    bool newHit;
    byte outputPin;
    byte inputPin;
    int msSinceLastHit;
    Recorder recorder;
    bool userPressing();
    void updateOneHitStatus();
    void resetOneHit();
//    void routeHitToRecorder();
//    void actuateHit();

};

#endif /* defined(__Amur__Hitter__) */

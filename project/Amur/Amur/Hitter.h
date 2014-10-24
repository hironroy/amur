//
//  Hitter.h
//  Amur
//
//  Created by Hiron Roy on 10/23/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Hitter__
#define __Amur__Hitter__

#include <iostream>
#include "StandardCplusplus.h"
#include "AmurIO.h"

class Hitter {
public:
    Hitter();
    void begin(int _hitDuration, byte _inputPin, byte _outputPin);
    void doHit();
    void handleInterval();
private:
    bool isDoingHit;
    int hitDuration;
    bool newHit;
    byte outputPin;
    byte inputPin;
    int msSinceLastHit;
};

#endif /* defined(__Amur__Hitter__) */

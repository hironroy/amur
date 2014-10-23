//
//  Metronome.h
//  Amur
//
//  Created by Hiron Roy on 10/22/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__Metronome__
#define __Amur__Metronome__

#include <iostream>
#include "AmurIO.h"

class Metronome {
public:
    Metronome(int _minBPM, int _maxBPM);
    int getCurrentDelay();
    float getCurrentBPM();
private:
    int minBPM;
    int maxBPM;
    int BPMRange;
    int maxTempoPotVal;
};

extern Metronome metronome;
#endif /* defined(__Amur__Metronome__) */

//
//  AmurIO.h
//  Amur
//
//  Created by Hiron Roy on 10/22/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__AmurIO__
#define __Amur__AmurIO__

#include <iostream>
#include "Arduino.h"

class AmurIO {
public:
    AmurIO();
    int getTempoPotVal();
    void metronomeLEDOn();
    void metronomeLEDOff();
    int sampleInterval;
private:
    //Inputs
    byte m_metronome;  //Analog input for Metronome Speed
    //Outputs
    byte m_metronome_led;  //Metronome Blinking
};

extern AmurIO amurIO;

#endif /* defined(__Amur__AmurIO__) */

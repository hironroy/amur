//
//  AmurIO.h
//  Amur
//
//  Created by Hiron Roy on 10/22/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__AmurIO__
#define __Amur__AmurIO__
#include "Arduino.h"
#include "AdafruitCapTouch.h"
#include "tBeat.h"

class AmurIO {
public:
    AmurIO();
    int getTempoPotVal();
    void metronomeLEDOn();
    void metronomeLEDOff();
    void blinkMetronomeLED();
    int sampleInterval;
    int debounceDuration;
    void pushTrigger(byte pincode);
    void lowTrigger(byte pincode);
    int readPin(byte pincode);
    int readCap(byte pincode);

private:
    //Inputs
    byte m_metronome;  //Analog input for Metronome Speed
    //Outputs
    byte m_metronome_led;  //Metronome Blinking
};

extern AmurIO amurIO;

#endif /* defined(__Amur__AmurIO__) */

//
//  AdafruitCapTouch.h
//  Amur
//
//  Created by Hiron Roy on 10/24/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#ifndef __Amur__AdafruitCapTouch__
#define __Amur__AdafruitCapTouch__

#include <iostream>
#include <Wire.h>
#include "Adafruit_MPR121.h"

class AdafruitCapTouch {
public:
    AdafruitCapTouch();
    void begin();
private:
    Adafruit_MPR121 capTouch;
    
};

extern AdafruitCapTouch touchDriver;
#endif /* defined(__Amur__AdafruitCapTouch__) */

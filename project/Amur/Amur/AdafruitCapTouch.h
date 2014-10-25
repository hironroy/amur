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
#include "StandardCplusplus.h"


class AdafruitCapTouch {
public:
    Adafruit_MPR121 touchAPI;
    void begin();
    int isPinUp(int pincode);
};

extern AdafruitCapTouch touchDriver;

#endif /* defined(__Amur__AdafruitCapTouch__) */

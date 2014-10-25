//
//  AdafruitCapTouch.cpp
//  Amur
//
//  Created by Hiron Roy on 10/24/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "AdafruitCapTouch.h"
#include "StandardCplusplus.h"

AdafruitCapTouch touchDriver;

AdafruitCapTouch::AdafruitCapTouch(){
    //leave blank
}
void AdafruitCapTouch::begin(){
    capTouch = Adafruit_MPR121();
    
    // Default address is 0x5A, if tied to 3.3V its 0x5B
    // If tied to SDA its 0x5C and if SCL then 0x5D
    if (!capTouch.begin(0x5A)) {
        Serial.println("MPR121 not found, check wiring?");
        while (1);
    }
    Serial.println("MPR121 found!");
}


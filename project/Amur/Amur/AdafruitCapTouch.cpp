//
//  AdafruitCapTouch.cpp
//  Amur
//
//  Created by Hiron Roy on 10/24/14.
//  Copyright (c) 2014 Hiron Roy. All rights reserved.
//

#include "AdafruitCapTouch.h"

AdafruitCapTouch touchDriver;

void AdafruitCapTouch::begin(){
    touchAPI = Adafruit_MPR121();
    Serial.println("Adafruit MPR121 Capacitive Touch sensor test");
    
    // Default address is 0x5A, if tied to 3.3V its 0x5B
    // If tied to SDA its 0x5C and if SCL then 0x5D
    if (!touchAPI.begin(0x5A)) {
        Serial.println("MPR121 not found, check wiring?");
        while (1);
    }
    Serial.println("MPR121 found!");
}

int AdafruitCapTouch::isPinUp(int pincode){
    uint16_t currtouched = touchAPI.touched();
    return currtouched & (1 <<pincode);
}
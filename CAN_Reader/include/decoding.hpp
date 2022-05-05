#ifndef DECODING_HPP
#define DECODING_HPP

#include <iostream>
#include "socketcan_cpp.h"

#define size 11

const static int drive = 100;
const static int neutral = 110;
const static int off = 111;
const static int park = 112;
const static int reverse = 114;
const static int on = 115;
const static int decelerate = 50;   //258
const static int accelerate = 56;   //259

using namespace std;

int decodedStart, decodedGear, decodedThrottle;

enum class gears {Park, Reverse, Neutral, Drive};

class decoding {
public:
    bool ignition = false;
    int throttle[size] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int *ptr = throttle;
    gears gear = gears::Park;

    bool decodeStart(const uint8_t &ignitionRequest)   {
        switch (ignitionRequest)
        {
        case on:   //user press 's' for start
            ignition = true;
            break;
        case off:   //user press 'o' for turn off
            ignition = false;
            break;

        default:
            break;
        }
    return ignition;
    }

    gears decodeGear(const uint8_t &gearRequest)   {
        switch (gearRequest)
        {
        case park:   //user press 'p' for park
            gear = gears::Park;
            break;
        case reverse:   //user press 'r' for reverse
            gear = gears::Reverse;
            break;
        case neutral:     //user press 'n' for neutral
            gear = gears::Neutral;
            break;
        case drive:   //user press 'd' for drive
            gear = gears::Drive;
            break;
        
        default:
            break;
        }
    return gear;
    }

    int decodeThrottle(const uint8_t &throttleRequest)   {
        switch (throttleRequest)
        {
        case accelerate:   //user press arrow up to increase throttle
            if(*ptr < 100)
            ptr++;
            break;
        case decelerate:   //user press arrow down to decrease throttle
            if(*ptr > 0)
            ptr--;
            break;

        default:
            break;
        }
    return *ptr;
    }

};

#endif  //DECODING_HPP
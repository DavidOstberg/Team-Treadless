#ifndef DECODING_HPP
#define DECODING_HPP

#include <iostream>
#include "socketcan_cpp.h"

const static int size = 11;

const static int minThrottle = 0;
const static int maxThrottle = 100;
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

class decoding {
public:
    bool ignition = false;
    int throttle[size] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int *ptr = throttle;
    char gear = 'P';

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

    char decodeGear(const uint8_t &gearRequest)   {
        switch (gearRequest)
        {
        case park:   //user press 'p' for park
            gear = 'P';
            break;
        case reverse:   //user press 'r' for reverse
            gear = 'R';
            break;
        case neutral:     //user press 'n' for neutral
            gear = 'N';
            break;
        case drive:   //user press 'd' for drive
            gear = 'D';
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
            if(*ptr < maxThrottle)
            ptr++;
            break;
        case decelerate:   //user press arrow down to decrease throttle
            if(*ptr > minThrottle)
            ptr--;
            break;

        default:
            break;
        }
    return *ptr;
    }

};

#endif  //DECODING_HPP
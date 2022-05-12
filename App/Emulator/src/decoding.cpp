#include "emulator.h"

Decoding::Decoding(){
    this -> ignition = false;
    this -> throttle = 0;
    this -> gear_stick = 'P';
    this -> throttle_delta = 5;
}

bool Decoding::DecodeStart(const uint8_t &ignition_request)   {
        switch (ignition_request)
        {
        case on:   //user press 'speed_get' for start
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

char Decoding::DecodeGearStick(const uint8_t &gear_stick_request)   {
        switch (gear_stick_request)
        {
        case park:   //user press 'p' for park
            gear_stick = 'P';
            break;
        case reverse:   //user press 'r' for reverse
            gear_stick = 'R';
            break;
        case neutral:     //user press 'n' for neutral
            gear_stick = 'N';
            break;
        case drive:   //user press 'd' for drive
            gear_stick = 'D';
            break;

        default:
            break;
        }
    return gear_stick;
    }

int Decoding::DecodeThrottle(const uint8_t &throttle_request)   {
        switch (throttle_request)
        {
        case accelerate:   //user press arrow up to increase throttle
            if(throttle < max_throttle)
            throttle += throttle_delta;
            break;
        case decelerate:   //user press arrow down to decrease throttle
            if(throttle > min_throttle)
            throttle -= throttle_delta;
            break;

        default:
            break;
        }
    return throttle;
    }
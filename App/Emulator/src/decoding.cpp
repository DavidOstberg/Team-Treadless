#include "emulator.h"

Decoding::Decoding()
{
    this->ignition = false;
    this->throttle = 0;
    this->gear_stick = 'P';
    this->throttle_delta = 5;
}

bool Decoding::DecodeStart(const uint8_t &ignition_request)
{
    switch (ignition_request)
    {
    case on: //user press 'speed_get' for start
        ignition = true;
        break;
    case off: //user press 'o' for turn off
        ignition = false;
        break;

    default:
        break;
    }
    return ignition;
}

int Decoding::DecodeGearStick(const uint8_t &gear_stick_request)
{
    switch (gear_stick_request)
    {
        //here could initilize
    case park: //user press 'p' for park
        gear_stick = 0;

        break;
    case reverse: //user press 'r' for reverse
        gear_stick = 2;
        break;
    case neutral: //user press 'n' for neutral
        gear_stick = 1;
        break;
    case drive: //user press 'd' for drive
        gear_stick = 3;
        break;

    default:
        break;
    }
    return gear_stick;
}

int Decoding::DecodeThrottle(const uint8_t &throttle_request, const uint8_t &gear_stick_request)
{
    //if gear in PRND the first time, set throttle to 0
    if(gear_stick_request){
        throttle=0;
    }

    switch (throttle_request)
    {
    case accelerate: //user press arrow up to increase throttle
        if (throttle < max_throttle)
            throttle += throttle_delta;
        break;
    case decelerate: //user press arrow down to decrease throttle
        if (throttle > min_throttle)
            throttle -= throttle_delta;
        break;

    default:
        break;
    }
    return throttle;
}
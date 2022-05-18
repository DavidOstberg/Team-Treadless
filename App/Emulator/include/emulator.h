#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <future>
#include <thread>
#include "reader.h"



const static int min_throttle = 0;
const static int max_throttle = 100;
const static int drive = 100;
const static int neutral = 110;
const static int off = 111;
const static int park = 112;
const static int reverse = 114;
const static int on = 115;
const static int decelerate = 50; //258
const static int accelerate = 56; //259
const static int min_temperature = 0;
const static int delta_temperature = 5;
const static int max_temperature = 100;
const static int idle = 800;
const static int max_speed_drive = 250;
const static int max_speed_reverse = 40;

const static float kmh_mph = 0.62;

class Decoding
{
public:
    bool ignition;
    int throttle, throttle_delta;
    char gear_stick;

    Decoding();

    bool DecodeStart(const uint8_t &ignition_request);

    int DecodeGearStick(const uint8_t &gear_stick_request);

    int DecodeThrottle(const uint8_t &throttle_request, const uint8_t &gear_stick_request);
};

class Emulator
{
public:

    void CalculateSpeed(Decoded_data *, const double);
    void CalculateGearNum(Decoded_data*);
    void CalculateRPM(Decoded_data*);
    void CalculateSpeedRPMGearLevel(Decoded_data*, std::atomic<bool> *);

    void CalculateRPMInNeutral(Decoded_data*);
    void CalculateTempeture(Decoded_data *_data);

};


void printing(Decoded_data *_data);

#endif //EMULATOR_H
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
const static int esc = 113;   //(Graceful shutdown)
const static int decelerate = 50; //258
const static int accelerate = 56; //259
const static int max_water_temperature = 150;
const static int delta_temperature = 5;
const static int max_oil_temperature = 110;
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

    void CalculateSpeedRPMGearLevel(Decoded_data*, std::atomic<bool> *);

    void CalculateSpeed(Decoded_data *, const double);

    void CalculateGearNum(Decoded_data*);

    void CalculateRPM(Decoded_data*);

    void CalculateRPMInNeutral(Decoded_data*);

    void CalculateOilWaterTemperature(Decoded_data *_data, std::atomic<bool> *);
  
    void CalculateFuel(Decoded_data *_data, std::atomic<bool> *);
};

void Engine_Transmission(Decoded_data *, std::atomic<bool> *);

void printing(Decoded_data *);

#endif //EMULATOR_H
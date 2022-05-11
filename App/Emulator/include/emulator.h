#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <future>
#include <thread>
#include "efuntions.h"
#include "socketcan_cpp.h"

using namespace std;

const static int min_throttle = 0;
const static int max_throttle = 100;
const static int drive = 100;
const static int neutral = 110;
const static int off = 111;
const static int park = 112;
const static int reverse = 114;
const static int on = 115;
const static int decelerate = 50;   //258
const static int accelerate = 56;   //259

const static int idle = 800;
const static int max_speed = 300;
//const static uint8_t max_throttle = 90;    //throttle[max]
const static int throttle_ratio = max_speed / max_throttle; // added in new main

const static float kmh_mph = 0.62;

// int speed = 0;
// int rpm = 0;
// int gear_num = 0;

int decoded_start, decoded_gear_stick, decoded_throttle;

class Decoding {
public:
    bool ignition;
    int throttle, throttle_delta;
    char gear_stick;

    //friend class Emulator;

//public:
    Decoding ();

    bool DecodeStart(const uint8_t &ignition_request);

    char DecodeGearStick(const uint8_t &gear_stick_request);

    int DecodeThrottle(const uint8_t &throttle_request);

};

class Emulator{
    public:
    //int decoded_start, decoded_gear, decoded_throttle;
    int speed;
    int rpm;
    int gear_num;

    //Emulator() = default;
    Emulator();

    int GetSpeed(int &throttle_get);
    int GetGearNum(int &speed_get);
    int GetRPM(int &speed_get, int &gear_num_get);
    void GetIgnition(/* void *arg */);
};


//testing for sending to dashboard
void SendToDashboard();

#endif //EMULATOR_H
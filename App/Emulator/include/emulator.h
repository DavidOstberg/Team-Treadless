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

int speed = 0;
int rpm = 0;
int gear_numb = 0;

int decoded_start, decoded_gear, decoded_throttle;

class decoding {
public:
    bool ignition = false;
    int throttle, throttle_delta = 5;
    char gear = 'P';

    bool DecodeStart(const uint8_t &ignition_request);

    char DecodeGear(const uint8_t &gear_request);

    int DecodeThrottle(const uint8_t &throttle_request);

};

decoding decode;
scpp::SocketCan sockat_can;

int GetSpeed(int &t);

int GetRPM(int &s, int gear_numb);

int GetIgnition(int &getStart);

int GetGearNumb(int &s);

#endif //EMULATOR_H
#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <future>
#include <thread>
#include "decoding.hpp"

const static int idle = 800;
//const static uint8_t max_speed = 300;
//const static uint8_t maxThrottle = 90;    //throttle[max]
//const static uint8_t throttleRatio = maxSpeed / maxThrottle; // added in new main

int speed = 0;
int rpm = 0;

int GetSpeed(int &t);

int GetRPM(int &s);

int GetIgnition(int &getStart);

#endif //EMULATOR_H
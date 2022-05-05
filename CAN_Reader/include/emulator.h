#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>
#include <future>
#include <thread>
#include "decoding.hpp"

const static uint8_t idle;
const static uint8_t maxSpeed = 300;
const static uint8_t maxThrottle = 90;    //throttle[max]
const static uint8_t throttleRatio = maxSpeed / maxThrottle;

int speed = 0;
int rpm = 0;

int getSpeed(int &t);

int getRPM(int &s);

int getIgnition(int &getStart);

#endif //EMULATOR_H
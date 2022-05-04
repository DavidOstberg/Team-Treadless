#include <iostream>
#include <future>
#include <thread>
#include "decoding.hpp"

const int idle = 800;
#define maxSpeed = 300;
#define maxThrottle = 90;    //throttle[max]
const throttleRatio = maxSpeed / maxThrottle;

int getSpeed(int &t)
{
    double speed;
    if(t<50)
    {
    speed = t*1.2;
    return speed;
    }
    else
    {
    speed = t*2;
    return speed;
    }

}
int getRPM(int &s)
{
   int rpm;
   if(s<100)
    {
    rpm = (s*13)+900;
    return rpm;
    }
    else
    {
    rpm = s*31;
    return rpm;
    }
   
}
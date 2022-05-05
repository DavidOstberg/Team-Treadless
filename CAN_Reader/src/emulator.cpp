#include "emulator.h"

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

int getIgnition(int &getStart){

    decoding canInput;
    uint8_t ignition = canInput.decodeStart(decodedStart);

    while(ignition){ //if ignition is ON
        switch(decodedGear){
            case 0: //Park
                speed = 0;
                rpm = idle;
                break;
            case 1:  //Reverse only gear1 - max 60km/h
                speed = getSpeed(decodedThrottle);  //*ptr from decoding.h
                rpm = getRPM(speed);
                break;
            case 2:  // Neutral
                speed = 0;
                rpm = idle;
                break;
            case 3:   // Drive
                speed = getSpeed(decodedThrottle);  //*ptr from decoding.h
                rpm = getRPM(speed);
                break;
            default:
                break;
        }
    }
}

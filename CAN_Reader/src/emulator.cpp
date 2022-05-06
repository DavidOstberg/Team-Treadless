#include "emulator.h"

int GetSpeed(int &t)
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

int GetRPM(int &s)
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

void GetIgnition(void *arg){

    decoding canInput;
    uint8_t ignition = canInput.decodeStart(decodedStart);

    while(ignition){ //if ignition is ON
        switch(decodedGear){
            case 'P': //Park
                speed = 0;
                rpm = idle;
                break;
            case 'R':  //Reverse only gear1 - max 60km/h
                speed = GetSpeed(decodedThrottle);  //*ptr from decoding.h
                rpm = GetRPM(speed);
                break;
            case 'N':  // Neutral
                speed = 0;
                rpm = idle;
                break;
            case 'D':   // Drive
                speed = GetSpeed(decodedThrottle);  //*ptr from decoding.h
                rpm = GetRPM(speed);
                break;
            default:
                break;
        }
    }
}


/*------- in MAIN -------
pthread_t temulator;
if(0 != pthread_create(&temulator, NULL, GetIgnition, &getStart))
return -1;

pthread_join(temulator, NULL);
*/

//std::thread temulator(GetIgnition);
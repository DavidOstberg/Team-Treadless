#include "emulator.h"



bool decoding::DecodeStart(const uint8_t &ignition_request)   {
        switch (ignition_request)
        {
        case on:   //user press 's' for start
            ignition = true;
            break;
        case off:   //user press 'o' for turn off
            ignition = false;
            break;

        default:
            break;
        }
    return ignition;
    }

char decoding::DecodeGear(const uint8_t &gear_request)   {
        switch (gear_request)
        {
        case park:   //user press 'p' for park
            gear = 'P';
            break;
        case reverse:   //user press 'r' for reverse
            gear = 'R';
            break;
        case neutral:     //user press 'n' for neutral
            gear = 'N';
            break;
        case drive:   //user press 'd' for drive
            gear = 'D';
            break;
        
        default:
            break;
        }
    return gear;
    }

int decoding::DecodeThrottle(const uint8_t &throttle_request)   {
        switch (throttle_request)
        {
        case accelerate:   //user press arrow up to increase throttle
            if(*ptr < max_throttle)
            ptr++;
            break;
        case decelerate:   //user press arrow down to decrease throttle
            if(*ptr > min_throttle)
            ptr--;
            break;

        default:
            break;
        }
    return *ptr;
    }

int GetSpeed(int &t)
{
    double speed;
    if(t<max_throttle/2)
    {
    speed = t*throttle_ratio;
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
   if(s<max_throttle)
    {
    rpm = (s*13)+idle;
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
    uint8_t ignition = canInput.DecodeStart(decoded_start);

    while(ignition){ //if ignition is ON
        switch(decoded_gear){
            case 'P': //Park
                speed = 0;
                rpm = idle;
                break;
            case 'R':  //Reverse only gear1 - max 60km/h
                speed = GetSpeed(decoded_throttle);  //*ptr from decoding.h
                rpm = GetRPM(speed);
                break;
            case 'N':  // Neutral
                speed = 0;
                rpm = idle;
                break;
            case 'D':   // Drive
                speed = GetSpeed(decoded_throttle);  //*ptr from decoding.h
                rpm = GetRPM(speed);
                break;
            default:
                break;
        }
    }
}


void reader(){
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
            std::cout << "Cannot open vcan0." << std::endl;
            std::cout << "Check whether the vcan0 interface is up!" << std::endl;
            exit (-1);
        }
        while (true) {
            scpp::CanFrame fr;
            if (sockat_can.read(fr) == scpp::STATUS_OK) {        
                printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x %02x  \n", fr.len, fr.id, 
                    fr.data[0], fr.data[1], fr.data[2], fr.data[3],
                    fr.data[4], fr.data[5], fr.data[6], fr.data[7]);

                decoded_start = decode.DecodeStart(fr.data[0]);
                decoded_gear = decode.DecodeGear(fr.data[1]);
                decoded_throttle = decode.DecodeThrottle(fr.data[2]);

                cout << "Ignition: " << decoded_start << endl;
                cout << "Gear: " << (char) decoded_gear << endl;
                cout << "Throttle: " << decoded_throttle << endl;
                cout << "Speed = " << GetSpeed(decoded_throttle) << endl;

            } else {
                for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
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
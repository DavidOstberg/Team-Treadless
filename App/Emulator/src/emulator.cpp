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
            if(throttle < max_throttle)
            throttle += throttle_delta;
            break;
        case decelerate:   //user press arrow down to decrease throttle
            if(throttle > min_throttle)
            throttle -= throttle_delta;;
            break;

        default:
            break;
        }
    return throttle;
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

int GetGearNumb(int &s)
{
    if(0 < s < 33)
    {
    gear_numb = 1;
    return gear_numb;
    }
    if(33 <= s < 66)
    {
    gear_numb = 2;
    return gear_numb;
    }
    if(66 <= s < 100)
    {
    gear_numb = 3;
    return gear_numb;
    }
    if(100 <= s < 133)
    {
    gear_numb = 4;
    return gear_numb;
    }
    if(133 <= s < 166)
    {
    gear_numb = 5;
    return gear_numb;
    }
    if(166 <= s)
    {
    gear_numb = 6;
    return gear_numb;
    }  
    
}
// D
int GetRPM(int &s, int gear_numb)
{
//    int rpm;
//    if(s<max_throttle)
//     {
//     rpm = (s*13)+idle;
//     return rpm;
//     }
//     else
//     {
//     rpm = s*31;
//     return rpm;
//     }
    if(gear_numb == 1 && s<33)
        {
        rpm = (s*33)+idle;
        return rpm;
        }
    else if(gear_numb == 2 && s<66)
        {
        rpm = (s*15)+idle;
        return rpm;
        }
     else if(gear_numb == 3 && s<100)
        {
        rpm = (s*12)+idle;
        return rpm;
        }
    else if(gear_numb == 4 && s<133)
        {
        rpm = (s*10)+idle;
        return rpm;
        }
    else if(gear_numb == 5 && s<166)
        {
        rpm = (s*10)+idle;
        return rpm;
        }
    else if(gear_numb == 6 && s<200)
        {
        rpm = (s*14)+idle;
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
                rpm = GetRPM(speed, gear_numb);
                break;
            case 'N':  // Neutral
                speed = 0;
                rpm = idle;
                break;
            case 'D':   // Drive
                speed = GetSpeed(decoded_throttle);  //*ptr from decoding.h
                rpm = GetRPM(speed, gear_numb);
                break;
            default:
                break;
        }
    }
}


void Reader(){
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
                cout << "Gear Stick: " << (char) decoded_gear << endl;
                cout << "Throttle: " << decoded_throttle << endl;

                cout << "Speed = " << GetSpeed(decoded_throttle) << endl;
                cout << "Gear = " << GetGearNumb(speed) << endl;
                cout << "RPM = " << GetRPM(speed, gear_numb) << endl;

                

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
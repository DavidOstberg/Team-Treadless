#include "emulator.h"

// -------------  EMULATOR Functions  -------------

/* Emulator emulator; */

Emulator::Emulator(){
    this -> speed = 0;
    this -> rpm = 0;
    this -> gear_num = 0;
}

/*struct emulator
    {
        int speed;

    };
    emulator engine;*/

void Emulator::GetSpeedRPMGearLevel(int decoded_start,int decoded_gear_stick,int decoded_throttle)
{


    if(decoded_start){
        switch( decoded_gear_stick){
            case 'P': //Park
                speed = 0;
                rpm = idle;

                break;
            case 'R':  //Reverse only gear 1 - max 60km/h
                speed = GetSpeed(decoded_throttle);
                rpm = GetRPM(speed, gear_num);
                break;
            case 'N':  // Neutral
                speed = 0;
                rpm = idle;
                break;
            case 'D':   // Drive
                speed = GetSpeed(decoded_throttle);
                gear_num = GetGearNum(speed);
                rpm = GetRPM(speed, gear_num);

                break;
            default:
                break;
            std::cout << "Speed = " << speed << std::endl;
            std::cout << "Gear No = " << gear_num << std::endl;
            std::cout << "RPM = " << rpm << std::endl;
        }
        //return engine
    }
}

int Emulator::GetSpeed(int &throttle_get)
{
    if(throttle_get < max_throttle){
        speed = throttle_get*throttle_ratio;
    }
    return speed;
}

int Emulator::GetGearNum(int &speed_get)
{
    if(speed_get >= 0 && speed_get <= 60){
        gear_num = 1;
    }
    else if(speed_get > 60 && speed_get <= 80){
        gear_num = 2;
    }
    else if(speed_get > 80 && speed_get <= 118){
        gear_num = 3;
    }
    else if(speed_get > 118 && speed_get <= 170){
        gear_num = 4;
    }
    else if(speed_get > 170 && speed_get <= 200){
        gear_num = 5;
    }
    else if(200 < speed_get){
        gear_num = 6;
    }
    else{
        std::cout << "Transmission failure";
    }
    return gear_num;
}

int Emulator::GetRPM(int &speed_get, int &gear_num_get)
{
    int gear_num_ratio;
    if(gear_num_get == 1 && speed_get<=60)
        {
            gear_num_ratio = 33;
        }
    else if(gear_num_get == 2 && speed_get<=80)
        {
            gear_num_ratio= 15;
        }
     else if(gear_num_get == 3 && speed_get<=118)
        {
            gear_num_ratio= 12;
        }
    else if((gear_num_get == 4 && speed_get<=170) ||(gear_num_get == 5 && speed_get<=200))
        {
            gear_num_ratio= 10;
        }
    else if(gear_num_get == 6 && speed_get<300)
        {
            gear_num_ratio= 14;
        }
    rpm = (speed_get*gear_num_ratio)+idle;

    return rpm;
}

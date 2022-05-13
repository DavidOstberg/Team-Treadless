#include "emulator.h"

void Engine_Transmission(Decoded *_data, std::atomic<bool> *_exit_flag)  {

    Emulator emulator;
    emulator.CalculateSpeedRPMGearLevel(_data,_exit_flag);


}


void Emulator::CalculateSpeedRPMGearLevel(Decoded *_data, std::atomic<bool> *_exit_flag)
{
while (!_exit_flag->load())
{


    if(_data->decoded_start){
        switch( _data->decoded_gear_stick){
            case 'P': //Park
                _data->speed = 0;
                rpm = idle;

                break;
            case 'R':  //Reverse only gear 1 - max 60km/h
                _data->speed = CalculateSpeed(_data);
                rpm = CalculateRPM(_data->speed, gear_num);
                break;
            case 'N':  // Neutral
                _data->speed = 0;
                rpm = idle;
                break;
            case 'D':   // Drives
                _data->speed = CalculateSpeed(_data);
                gear_num = CalculateGearNum(_data->speed);
                rpm = CalculateRPM(_data->speed, gear_num);

                std::cout << std::endl;
                std::cout << "Gear stick = " << (char)_data->decoded_gear_stick << std::endl;
                std::cout << "Gear No = " << gear_num << std::endl;
                std::cout << "Throttle = "<<_data->decoded_throttle <<std::endl;
                std::cout << std::endl;
                std::cout << "Speed = " << _data->speed << std::endl;
                std::cout << "RPM = " << rpm << std::endl;
                std::cout << std::endl;


                std::this_thread::sleep_for(std::chrono::seconds(1));

                break;


            default:
                break;

        }
        //return engine
    }
}
}

int Emulator::CalculateSpeed(Decoded *_data)
{
    if(_data->decoded_throttle < max_throttle){
        _data->speed = _data->decoded_throttle *throttle_ratio;
    }
    return _data->speed;
}

int Emulator::CalculateGearNum(int &speed_get)
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

int Emulator::CalculateRPM(int &speed_get, int &gear_num_get)
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


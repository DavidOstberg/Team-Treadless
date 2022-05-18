#include "emulator.h"

void Engine_Transmission(Decoded_data *_data, std::atomic<bool> *_exit_flag)
{
    Emulator emulator;
    emulator.CalculateSpeedRPMGearLevel(_data, _exit_flag);
}

void Emulator::CalculateSpeedRPMGearLevel(Decoded_data *_data, std::atomic<bool> *_exit_flag)
{
    while (!_exit_flag->load())
    {
        if (_data->decoded_start)
        {
            switch (_data->decoded_gear_stick)
            {
            case 0: //Park

                _data->speed = 0;
                _data->rpm = idle;


                break;

            case 1: // Neutral

                _data->speed = 0;
                _data->gear_num = 0;
                CalculateRPMInNeutral(_data);

                break;

            case 2: //Reverse only gear 1 - max 40km/h

                _data->gear_num = 1;
                CalculateSpeed(_data, max_speed_reverse);
                CalculateRPM(_data);

                break;

            case 3: // Drive

                CalculateSpeed(_data, max_speed_drive);
                CalculateGearNum(_data);
                CalculateRPM(_data);

                break;

            default:
                break;
            }

            printing(_data);
        }
        else
        { // ignition OFF
            _data->decoded_gear_stick = 1;
            _data->decoded_throttle = 0;
            _data->gear_num = 0;
            _data->rpm = 0;
            _data->speed = 0;
            _data->water_temperature = 0;
            _data->oil_temperature = 0;
        }
    }
}

void Emulator::CalculateOilWaterTemperature(Decoded_data *_data, std::atomic<bool> *_exit_flag)
{
    while ((_data->oil_temperature < max_oil_temperature)&&(_data->water_temperature < max_water_temperature)&& (!_exit_flag->load()))
    {
        _data->oil_temperature +=   delta_temperature;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "OIL TEMPERATURE = " << _data->oil_temperature << std::endl;
        _data->water_temperature += delta_temperature;
        std::cout << "WATER TEMPERATURE = " << _data->water_temperature << std::endl;
    }    
}


void Emulator::CalculateSpeed(Decoded_data *_data, const double _max_speed)
{
    double throttle_ratio = _max_speed / max_throttle;
    _data->speed = (_data->decoded_throttle * throttle_ratio);
}

void Emulator::CalculateGearNum(Decoded_data *_data)
{
    if (_data->speed >= 0 && _data->speed <= 60)
    {
        _data->gear_num = 1;
    }
    else if (_data->speed > 60 && _data->speed <= 80)
    {
        _data->gear_num = 2;
    }
    else if (_data->speed > 80 && _data->speed <= 118)
    {
        _data->gear_num = 3;
    }
    else if (_data->speed > 118 && _data->speed <= 170)
    {
        _data->gear_num = 4;
    }
    else if (_data->speed > 170 && _data->speed <= 200)
    {
        _data->gear_num = 5;
    }
    else if (200 < _data->speed)
    {
        _data->gear_num = 6;
    }
    else
    {
        std::cout << "Transmission failure";
    }
}

void Emulator::CalculateRPM(Decoded_data *_data)
{
    int gear_num_ratio;
    if (_data->gear_num == 1 && _data->speed <= 60)
    {
        gear_num_ratio = 33;
    }
    else if (_data->gear_num == 2 && _data->speed <= 80)
    {
        gear_num_ratio = 15;
    }
    else if (_data->gear_num == 3 && _data->speed <= 118)
    {
        gear_num_ratio = 12;
    }
    else if ((_data->gear_num == 4 && _data->speed <= 170) || (_data->gear_num == 5 && _data->speed <= 200))
    {
        gear_num_ratio = 10;
    }
    else if (_data->gear_num == 6 && _data->speed < 300)
    {
        gear_num_ratio = 14;
    }
    _data->rpm = (_data->speed * gear_num_ratio) + idle;
}

void Emulator::CalculateRPMInNeutral(Decoded_data *_data)
{
    _data->rpm = (_data->decoded_throttle * 50) + idle;
}

int Packing_RPM::FirstDigitRPM(int rpm)
{
    return rpm / 100;
}

int Packing_RPM::SecondDigitRPM(int rpm)
{
    return rpm % 100;
}

void printing(Decoded_data *_data)
{
    std::cout << std::endl;
    std::cout << "Gear stick = " << _data->decoded_gear_stick << std::endl;
    std::cout << "Gear Num = " << _data->gear_num << std::endl;
    std::cout << "Throttle = " << _data->decoded_throttle << std::endl;
    std::cout << std::endl;
    std::cout << "Speed = " << _data->speed << std::endl;
    std::cout << "RPM = " << _data->rpm << std::endl;
    std::cout << std::endl;
    std::cout << "OIL TEMPERATURE = " << _data->oil_temperature << std::endl;
    std::cout << std::endl;
    std::cout << "WATER TEMPERATURE = " << _data->water_temperature << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

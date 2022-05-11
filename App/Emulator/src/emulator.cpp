#include "emulator.h"

// -------------  DEFINITION Decoding Class  -------------

Decoding::Decoding(){
    this -> ignition = false;
    this -> throttle = 0;
    this -> gear_stick = 'P';
    this -> throttle_delta = 5;
}

bool Decoding::DecodeStart(const uint8_t &ignition_request)   {
        switch (ignition_request)
        {
        case on:   //user press 'speed_get' for start
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

char Decoding::DecodeGearStick(const uint8_t &gear_stick_request)   {
        switch (gear_stick_request)
        {
        case park:   //user press 'p' for park
            gear_stick = 'P';
            break;
        case reverse:   //user press 'r' for reverse
            gear_stick = 'R';
            break;
        case neutral:     //user press 'n' for neutral
            gear_stick = 'N';
            break;
        case drive:   //user press 'd' for drive
            gear_stick = 'D';
            break;

        default:
            break;
        }
    return gear_stick;
    }

int Decoding::DecodeThrottle(const uint8_t &throttle_request)   {
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

// -------------  READER Function  -------------
void Reader(){
    Decoding decode;
    scpp::SocketCan sockat_can;
    scpp::SocketCan socket_dash;

    scpp::CanFrame fr;
    Emulator emulator;

    if (sockat_can.open("vcan0") != scpp::STATUS_OK ){
            std::cout << "Cannot open vcan0." << std::endl;
            std::cout << "Check whether the vcan0 interface is up!" << std::endl;
            exit (-1);
        }
    if (socket_dash.open("vcan1") != scpp::STATUS_OK){
                 std::cout << "Cannot open vcan1." << std::endl;
                std::cout << "Check whether the vcan0 interface is up!" << std::endl;
                exit (-1);
                }

        while (true) {
            //scpp::CanFrame fr;   ?????????
            if (sockat_can.read(fr) == scpp::STATUS_OK) {
                cout << endl;
                printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x %02x  \n", fr.len, fr.id,
                    fr.data[0], fr.data[1], fr.data[2], fr.data[3],
                    fr.data[4], fr.data[5], fr.data[6], fr.data[7]);

                decoded_start = decode.DecodeStart(fr.data[0]);
                decoded_gear_stick = decode.DecodeGearStick(fr.data[1]);
                decoded_throttle = decode.DecodeThrottle(fr.data[2]);

                cout << "Ignition: " << decoded_start << endl;
                cout << "Gear Stick: " << (char)  decoded_gear_stick << endl;
                cout << "Throttle: " << decoded_throttle << endl;

                //emulator.GetIgnition();

            } else {
                std::cout << "hello"<<std::endl;
                SendToDashboard();
                // for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?


            }

        }
}

/***Send to dashboard for testing*****************/
void SendToDashboard()  {
    int array[3];
    scpp::CanFrame cf_to_dashboard;
    scpp::SocketCan socket_dash;
    cf_to_dashboard.id = 111;
    cf_to_dashboard.len = 3;

    for(int i = 0; i < 3; i++)  {
        (cf_to_dashboard.data)[i] = 33;
    }
    socket_dash.write(cf_to_dashboard);
}

// -------------  EMULATOR Functions  -------------

/* Emulator emulator; */

Emulator::Emulator(){
    this -> speed = 0;
    this -> rpm = 0;
    this -> gear_num = 0;
}

void Emulator::GetIgnition(/* void *arg */){

    //decoded_start = decode.DecodeStart(fr.data[0]);

    if(decoded_start){ //if ignition is ON
        switch( decoded_gear_stick){
            case 'P': //Park
                speed = 0;
                rpm = idle;
                cout << "We are in P" << endl;  //To verify we are in
                cout << "Speed = " << speed << endl;
                cout << "Gear No = " << GetGearNum(speed) << endl;
                cout << "RPM = " << idle << endl;
                break;
            case 'R':  //Reverse only gear1 - max 60km/h
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
                // rpm = GetRPM(speed, gear_num);
                cout << "We are in D" << endl;   //To verify we are in
                cout << "Speed = " << speed << endl;
                cout << "Gear No = " << gear_num << endl;
                cout << "RPM = " << rpm << endl;
                break;
            default:
                break;
        }
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



/*------- in MAIN -------
pthread_t temulator;
if(0 != pthread_create(&temulator, NULL, GetIgnition, &getStart))
return -1;
pthread_join(temulator, NULL);
*/

//std::thread temulator(GetIgnition);
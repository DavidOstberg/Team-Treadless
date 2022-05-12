#include "reader.h"
#include "emulator.h"

void Reader(Decoded *_decoded, std::atomic<bool> *_exit_flag)
{
    Decoding decode;
    scpp::SocketCan sockat_can;
    scpp::SocketCan socket_dash;

    scpp::CanFrame fr;

    //Decoded decoded;

    unsigned int input_handler_fr_id =1;

    if (sockat_can.open("vcan0") != scpp::STATUS_OK)
    {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit(-1);
    }


    while (!_exit_flag->load())
    {
        //scpp::CanFrame fr;   ?????????
        if (sockat_can.read(fr) == scpp::STATUS_OK)
        {
            std::cout << std::endl;
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x %02x  \n", fr.len, fr.id,
                   fr.data[0], fr.data[1], fr.data[2], fr.data[3],
                   fr.data[4], fr.data[5], fr.data[6], fr.data[7]);

            _decoded->decoded_start = decode.DecodeStart(fr.data[0]);
            _decoded->decoded_gear_stick = decode.DecodeGearStick(fr.data[1]);
            _decoded->decoded_throttle = decode.DecodeThrottle(fr.data[2]);


            std::cout << "Ignition: " << _decoded->decoded_start << std::endl;
            std::cout << "Gear Stick: " << (char)_decoded->decoded_gear_stick << std::endl;
            std::cout << "Throttle: " << _decoded->decoded_throttle << std::endl;

            // emulator.GetSpeedRPMGearLevel(decoded_start, decoded_gear_stick, decoded_throttle);

        }
        else
        {

            // std::cout << "hello"<<std::endl;
            SendToDashboard(_decoded->decoded_start);
            for (size_t i = 0; i < 9999; i++)
                ; //STUPID SLEEP?
        }
    }
   // return *_decoded;
}

/***Send to dashboard for testing*****************/
void SendToDashboard(int decoded_start_)
{

    scpp::CanFrame cf_to_dashboard;
    scpp::SocketCan socket_dash;
    cf_to_dashboard.id = 111;
    cf_to_dashboard.len = 3;

    if (socket_dash.open("vcan1") != scpp::STATUS_OK)
            {
                std::cout << "Cannot open vcan1." << std::endl;
                std::cout << "Check whether the vcan1 interface is up!" << std::endl;
                exit(-1);
            }
    //std::cout << "the ignition is";
    for (int i = 0; i < 3; i++)
    {
        cf_to_dashboard.data[i] = decoded_start_;
    }
    socket_dash.write(cf_to_dashboard);
}

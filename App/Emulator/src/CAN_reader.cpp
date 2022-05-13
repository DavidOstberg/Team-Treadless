#include "reader.h"
#include "emulator.h"


void Reader(Decoded* _decoded, std::atomic<bool> *_exit_flag, scpp::SocketCan &sockat_can, scpp::SocketCan &socket_dash)
{
    Decoding decode;

    scpp::CanFrame fr;

    //Decoded decoded;

    unsigned int input_handler_fr_id =1;


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

        }
        else
        {
            std::cout << "=========================================\n";
            std::cout << "Sending to dashboard\n";

            SendToDashboard(_decoded, socket_dash);
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }
    }

}

/***Send to dashboard for testing*****************/
void SendToDashboard(Decoded* _decoded, scpp::SocketCan &socket_dash)
{

    scpp::CanFrame cf_to_dashboard;

    cf_to_dashboard.id = 111;
    cf_to_dashboard.len = 3;


    //std::cout << "the ignition is";


    cf_to_dashboard.data[0] = _decoded->decoded_start;
    cf_to_dashboard.data[1] = _decoded->decoded_gear_stick;
    cf_to_dashboard.data[2] = _decoded->speed;

    socket_dash.write(cf_to_dashboard);
}

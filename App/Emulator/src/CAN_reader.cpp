#include "reader.h"
#include "emulator.h"

void Reader(Decoded_data *_decoded, std::atomic<bool> *_exit_flag, scpp::SocketCan &sockat_can, scpp::SocketCan &socket_dash)
{
    Decoding decode;
    scpp::CanFrame fr;

    unsigned int input_handler_fr_id = 1;

    while (!_exit_flag->load())
    {
        if (sockat_can.read(fr) == scpp::STATUS_OK)
        {
            std::cout << std::endl;
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x %02x  \n", fr.len, fr.id,
                   fr.data[0], fr.data[1], fr.data[2], fr.data[3],
                   fr.data[4], fr.data[5], fr.data[6], fr.data[7]);

        //SharedBuffer THIS_IS_SHARED_AMONGST_BOTH_THREADS;

        //Decoded_data decoded;

        { //open lock scope
           std::lock_guard<std::mutex> lock(_decoded->m);
           _decoded->decoded_start = decode.DecodeStart(fr.data[0]);
           _decoded->decoded_gear_stick = decode.DecodeGearStick(fr.data[1]);
           _decoded->decoded_throttle = decode.DecodeThrottle(fr.data[2], fr.data[1]);
        } //close lock scope


       //THIS_IS_SHARED_AMONGST_BOTH_THREADS.write(decoded);


            std::cout << "Ignition: " << _decoded->decoded_start << std::endl;
            std::cout << "Gear Stick: " << /* (char) */_decoded->decoded_gear_stick << std::endl;
            std::cout << "Throttle: " << _decoded->decoded_throttle << std::endl;
        }

        std::cout << "=========================================\n";
        std::cout << "Sending to dashboard\n";

        SendToDashboard(_decoded, socket_dash);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //}
    }
}

/***Send to dashboard for testing*****************/
void SendToDashboard(Decoded_data *_decoded, scpp::SocketCan &socket_dash)
{

    scpp::CanFrame cf_to_dashboard;
    Packing_RPM packed_rpm;

    cf_to_dashboard.id = 0x123;

    cf_to_dashboard.len = 8;


    cf_to_dashboard.data[0] = _decoded->decoded_start;
    cf_to_dashboard.data[1] = _decoded->decoded_gear_stick;
    cf_to_dashboard.data[2] = _decoded->speed;

    cf_to_dashboard.data[3] = _decoded->gear_num;

    cf_to_dashboard.data[6] = _decoded->oil_temperature;
    cf_to_dashboard.data[7] = _decoded->water_temperature;

    cf_to_dashboard.data[4] = packed_rpm.FirstDigitRPM(_decoded->rpm);
    cf_to_dashboard.data[5] = packed_rpm.SecondDigitRPM(_decoded->rpm);


    socket_dash.write(cf_to_dashboard);
}
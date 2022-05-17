#include <iostream>

#include <thread>
#include<emulator.h>

void Engine_Transmission(Decoded_data *_start_gearstick_throttle, std::atomic<bool> *exit_flag);

int main() {

    scpp::SocketCan sockat_can;
    scpp::SocketCan socket_dash;

    if (sockat_can.open("vcan0") != scpp::STATUS_OK)
    {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit(-1);
    }

     if (socket_dash.open("vcan1") != scpp::STATUS_OK)
            {
                std::cout << "Cannot open vcan1." << std::endl;
                std::cout << "Check whether the vcan1 interface is up!" << std::endl;
                exit(-1);
            }

    Decoded_data decoded;
    decoded.temperature =0;  //delete after we add default values

    std::atomic<bool> exit_flag(false);

    std::thread CANReaderThread(Reader, &decoded, &exit_flag, std::ref(sockat_can), std::ref(socket_dash));
    std::thread EngineTransmissionThread(Engine_Transmission, &decoded, &exit_flag);
    Emulator temp;
    temp.CalculateTempeture(&decoded); 

    CANReaderThread.join();
    EngineTransmissionThread.join();


    return 0;
}

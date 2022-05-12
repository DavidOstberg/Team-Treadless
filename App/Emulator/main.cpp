#include <iostream>
#include "reader.h"
#include <thread>

//#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

void Engine_Transmission(Decoded *_start_gearstick_throttle, std::atomic<bool> *exit_flag);

int main() {
    Decoded decoded;


    //Decoded start_gearstick_throttle=
    //Reader(decoded);
    std::cout<< "i am in main";
    std::atomic<bool> exit_flag(false);
    std::thread CANReaderThread(Reader, &decoded, &exit_flag);

    //


    //Engine_Transmission(decoded)

    std::thread EngineTransmissionThread(Engine_Transmission, &decoded, &exit_flag);
    CANReaderThread.join();
    EngineTransmissionThread.join();

    //for(;;){}


    return 0;
}

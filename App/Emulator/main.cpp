#include <iostream>
#include "reader.h"
#include <thread>


void Engine_Transmission(Decoded *_start_gearstick_throttle, std::atomic<bool> *exit_flag);

int main() {
    Decoded decoded;

    std::atomic<bool> exit_flag(false);

    std::thread CANReaderThread(Reader, &decoded, &exit_flag);
    std::thread EngineTransmissionThread(Engine_Transmission, &decoded, &exit_flag);

    CANReaderThread.join();
    EngineTransmissionThread.join();


    return 0;
}

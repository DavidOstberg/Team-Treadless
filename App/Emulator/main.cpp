#include <iostream>
#include "reader.h"
#include <thread>

//#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

void Engine_Transmission(Decoded _start_gearstick_throttle);

int main() {
    Decoded decoded;


    //Decoded start_gearstick_throttle=
    Reader(decoded);
    std::cout<< "i am in main";
    //std::thread CANReaderThread(Reader, decoded);
    std::cout << "engine started??"<<decoded.decoded_start<<std::endl;
    std::cout << "engine gear number??"<<(char)decoded.decoded_gear_stick<<std::endl;
    std::cout << "engine throttle??"<<decoded.decoded_throttle<<std::endl;





    Engine_Transmission(decoded);




    return 0;
}

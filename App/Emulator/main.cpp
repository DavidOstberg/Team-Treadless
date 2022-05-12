#include <iostream>
#include "reader.h"
#include <thread>

//#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

void Engine_Transmission(Decoded _start_gearstick_throttle);

int main() {

    Decoded start_gearstick_throttle=Reader();
    std::cout<< "i am in main";


    Engine_Transmission(start_gearstick_throttle);




    return 0;
}

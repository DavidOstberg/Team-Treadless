#include <iostream>
#include <future>
#include <thread>
#include "decoding.hpp"
#include "emulator.h"



int main (){
int speed = 0;
int rmp = 0;


//IGNITION CONDITION
// if (ignition == true){   // do it with ? and :
//     return speed = 0 && rmp = 800;
// }else{
//     return(-1)
// }

decodeStart(1);

while(ignition){
    switch(gear){
        case 0: //Park
            speed = 0;
            rmp = idle;
            break;
        case 1:  //Reverse only gear1 - max 60km/h
            speed = getSpeed(*ptr);  //*ptr from decoding.h
            rpm = getRPM()
            break;
        case 2:  // Neutral
            speed = 0;
            rmp = idle;
            break;
        case 3:   // Drive
            CalculateSpeed();
            break;
        default:
            break;
    }
}


// if (ignition == true && (gear = gears::Drive || gear = gears::Reverse)){

// }


    return 0;
}
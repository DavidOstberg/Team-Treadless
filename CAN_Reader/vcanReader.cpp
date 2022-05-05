#include <iostream>
#include "decoding.hpp"

#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

using namespace std;

int main() {
    decoding decode;
    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
    while (true) {
        scpp::CanFrame fr;
        if (sockat_can.read(fr) == scpp::STATUS_OK) {        
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x %02x  \n", fr.len, fr.id, 
                fr.data[0], fr.data[1], fr.data[2], fr.data[3],
                fr.data[4], fr.data[5], fr.data[6], fr.data[7]);

            decodedStart = decode.decodeStart(fr.data[0]);
            decodedGear = (int) decode.decodeGear(fr.data[1]);
            decodedThrottle = decode.decodeThrottle(fr.data[2]);

            cout << "Ignition: " << decodedStart << endl;
            cout << "Gear: " << (int) decodedGear << endl;
            cout << "Throttle: " << decodedThrottle << endl;
        } else {
            for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
        }
    }
    return 0;
}

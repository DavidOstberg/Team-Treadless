#include <iostream>
#include "socketcan_cpp.h"
#include "ncurseInput.hpp"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    scpp::SocketCan sockat_can;
    uint8_t input_array[8]{};

    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }

    while (true) {
        scpp::CanFrame cf_to_write;

        cf_to_write.id = 1;
        cf_to_write.len = 8;

        ncurseInput(input_array);

        memcpy(cf_to_write.data, input_array, sizeof(input_array));

        auto write_sc_status = sockat_can.write(cf_to_write);
        if (write_sc_status != scpp::STATUS_OK)
            printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
        else
            printf("Message was written to the socket \n");
    }

    return 0;
}










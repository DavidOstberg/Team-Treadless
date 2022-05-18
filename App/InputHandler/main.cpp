#include "ncurseInput.hpp"

int main() {

    scpp::SocketCan sockat_can;
    uint8_t input_array[8]{};
    scpp::CanFrame cf_to_write;

    if (sockat_can.open("vcan0") != scpp::STATUS_OK)
    {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    bool InputHandlerRunning = true;
    uint8_t ExitCounter = 3; 

    while (InputHandlerRunning) {
   
        cf_to_write.id = 1;
        cf_to_write.len = 8;

        if(ncurseInput(input_array))   //return function defined on .cpp file (Graceful shutdown)
        {  
            for (int i = 0; i < ExitCounter; i++)   //we send 3 times the message to be sure we are receiving the quit input
            {
                memcpy(cf_to_write.data, input_array, sizeof(input_array));
                auto write_sc_status = sockat_can.write(cf_to_write);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            break;
        } 

        memcpy(cf_to_write.data, input_array, sizeof(input_array));
        auto write_sc_status = sockat_can.write(cf_to_write);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (write_sc_status != scpp::STATUS_OK)
        {
            printf("something went wrong on socket write, error code : %d \r\n", int32_t(write_sc_status));
        }
        else
        {
            printf(" Message was written to the socket \r\n");
        }
    }
    
    endwin();  // down ncurses (Graceful shutdown)
    
    return 0;
}










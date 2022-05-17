#ifndef EFUNCTIONS_H
#define EFUNCTIONS_H
#include <atomic>
#include <mutex>
#include "socketcan_cpp.h"

//Decoded name should be data and consider to use class
struct Decoded_data {
    int decoded_start;
    int decoded_gear_stick;
    int decoded_throttle;

    int speed;
    int gear_num;
    int rpm;
    int temperature;
    std::mutex m;  
    };

void Reader(Decoded_data *, std::atomic<bool> *, scpp::SocketCan&, scpp::SocketCan&);

//testing for sending to dashboard
void SendToDashboard(Decoded_data*, scpp::SocketCan&);


#endif  //EFUNCTIONS_H
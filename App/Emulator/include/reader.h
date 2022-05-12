#ifndef EFUNCTIONS_H
#define EFUNCTIONS_H
#include <atomic>


#include "socketcan_cpp.h"
struct Decoded {
    int decoded_start, decoded_gear_stick, decoded_throttle;
    };
void Reader(Decoded *, std::atomic<bool> *);
//testing for sending to dashboard
void SendToDashboard(int);


#endif  //EFUNCTIONS_H
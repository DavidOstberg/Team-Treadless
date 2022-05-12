#ifndef EFUNCTIONS_H
#define EFUNCTIONS_H

#include "socketcan_cpp.h"
struct Decoded {
    int decoded_start, decoded_gear_stick, decoded_throttle;
    };
Decoded Reader(Decoded &);
//testing for sending to dashboard
void SendToDashboard(int);


#endif  //EFUNCTIONS_H
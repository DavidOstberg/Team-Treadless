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
    
/* class SharedBuffer {

    Decoded_data d;
    std::mutex m;
    void write(Decoded_data _other) {
        //lock 
        1) std::memcpy(_other,d,sizeof(struct Decoded_data)); or
        2) d.speed = _other.speed;

    }
    Decoded_data read()
    {
        Decoded_data ret;
        //lock 
        ret.speed = d.speed;

        return ret;

    }  
    void makeDefault(){
       std::lock_guard<std::mutex> lock(m); 
       d.decoded_gear_stick = 0;
       d.decoded_throttle = 0;
       d.gear_num = 0;
       d.rpm = 0;
       d.speed = 0;
    }
}; */

void Reader(Decoded_data *, std::atomic<bool> *, scpp::SocketCan&, scpp::SocketCan&);

//testing for sending to dashboard
void SendToDashboard(Decoded_data*, scpp::SocketCan&);

// Not cool packing!
class Packing_RPM
{

public:

    int FirstDigitRPM(int rpm);
    int SecondDigitRPM(int rpm);

};


#endif  //EFUNCTIONS_H
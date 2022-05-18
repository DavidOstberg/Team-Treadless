#ifndef NCURSESINPUT_HPP
#define NCURSESINPUT_HPP
#include <curses.h>
#include <thread>
#include "socketcan_cpp.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


bool ncurseInput(uint8_t array[]);


#endif  // NCURSESINPUT_HPP
#include <curses.h>
#include <iostream>
#include "keyMapping.hpp"
#include "ncurseInput.hpp"

void ncurseInput(uint8_t array[])
{

    int ch;
    initscr();

    if (((ch) = getch()) != ERR)
    {
        if (ch == key_s ||ch == key_o)
        {
            array[0] = ch;
        }
        else if (ch == key_d || ch == key_r || ch == key_p || ch == key_n)
        {
            array[1] = ch;
        }
        else if (ch == key_up || ch == key_down)
        {
            array[2] = ch;
        }
        else
        {
            std::cout << "not valid input \n";
        }
    }
}

/*void ncurseInput(uint8_t array[]) {
    initscr();
    int ch;
    for (int i=0;i<lenOfFrame;i++) {
        //   if (((ch) = getch()) == ERR) {
        //       std::cout<< "invalid input";
        //  }
         if((i<activeCell)&&(((ch) = getch()) != ERR))
        {
            std::cout << "Input is " << ch << std::endl;
            array[i]=ch;
        }
        else{
                array[i]=0;
            }
    }


}*/

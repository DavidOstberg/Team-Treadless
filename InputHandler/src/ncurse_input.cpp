#include <curses.h>
#include <iostream>
#define lenOfFrame 8
#define activeCell 3

void ncurseInput(uint8_t array[]) {
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

    //endwin();
}

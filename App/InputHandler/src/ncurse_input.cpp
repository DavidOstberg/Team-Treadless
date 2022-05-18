
#include "keyMapping.hpp"
#include "ncurseInput.hpp"

bool ncurseInput(uint8_t array[])
{
    int ch;
    bool exit = false;  //in order to down the while loop of InputHandle when we enter 'q' (Graceful shutdown)

    if (((ch) = getch()) != ERR)
    {
        if (ch == key_s || ch == key_o)
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
        else if (ch == key_esc)  //(Graceful shutdown)
        {
            array[0] = key_o;
            array[3] = ch; // to kill Emulator
            exit = true;  // to kill Input Handler
        }
        else
        {
            std::cout << ch <<" not valid input \r\n";
        }
    }
    else
    {
        array[1] = 0;
        array[2] = 0;
    }
    return exit;  // we return the bool of case ch == key_esc
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

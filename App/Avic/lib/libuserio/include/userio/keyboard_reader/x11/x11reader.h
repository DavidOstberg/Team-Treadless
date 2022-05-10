#ifndef X11READER_H
#define X11READER_H
#include <X11/Xlib.h>
#include <utility>
//#include <cstdint>

class KeyBoardReaderForX11 {
public:
    using KeyBehaviour_t = std::pair<int,unsigned int>;
    using Key_t = KeyBehaviour_t::second_type;



    KeyBoardReaderForX11();
    KeyBoardReaderForX11(const KeyBoardReaderForX11&) = delete;
    KeyBoardReaderForX11 operator = (const KeyBoardReaderForX11&) = delete;
    ~KeyBoardReaderForX11();
    KeyBehaviour_t readKeyBehaviour();
private:

    XEvent   event;
    Display  *display;
};








#endif // X11READER_H

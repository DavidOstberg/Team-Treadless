#ifndef UIO_TYPES_H
#define UIO_TYPES_H
#include "keyboard_reader/x11/x11reader.h"
#include "userIO_intf.hpp"

typedef UserInputReader<KeyBoardReaderForX11> x11KeyboardReader;
#endif // UIO_TYPES_H

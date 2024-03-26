#ifndef SQUARE_H
#define SQUARE_H
#include "GameObject.h"

class Square : public GameObject {
public:
    bool bomb;
    bool revealed;
    bool flagged;
    int bombsNearby;
    Square();
};

#endif // SQUARE_H
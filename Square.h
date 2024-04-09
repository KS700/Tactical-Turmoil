#ifndef SQUARE_H
#define SQUARE_H

#include "GameObject.h"

// Square Class - Inheritance from GameObject
class Square : public GameObject {
public:
    bool bomb;          // Indicates whether the square contains a bomb
    bool revealed;      // Indicates whether the square has been revealed/selected
    bool flagged;       // Indicates whether the square has been flagged
    int bombsNearby;    // Number of bombs nearby this square
    Square();           // Default constructor
};

#endif // SQUARE_H
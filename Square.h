#ifndef SQUARE_H
#define SQUARE_H

class Square {
public:
    bool bomb;
    bool revealed;
    bool flagged;
    int bombsNearby;
    Square();
};

#endif // SQUARE_H
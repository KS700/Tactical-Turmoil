// GameObject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <string>

// Declaration of the GameObject class
class GameObject {
protected:
    int x; // x-coordinate
    int y; // y-coordinate
public:
    // Constructor with parameters to initialize x and y coordinates
    GameObject(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    // Default constructor initializing x and y coordinates to 0
    GameObject() : x(0), y(0) {}

    // Common method to display information about the game object
    virtual void display() const {
        std::cout << "GameObject at position (" << x << ", " << y << ")" << std::endl;
    }

    // Virtual destructor to allow proper cleanup of derived classes
    virtual ~GameObject() {}
};

#endif // GAMEOBJECT_H

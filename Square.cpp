#include "Square.h"

// Constructor for Square class
Square::Square() : bomb(false), revealed(false), flagged(false), bombsNearby(0) {}

// Initialize bomb status, revealed status, and flagged status to false
// Initialize number of nearby bombs to 0
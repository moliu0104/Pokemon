#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <cstdlib>
#include <ctime>

// Define a namespace for utility functions related to randomness
namespace util {

    // Initializes the random number generator with the current time
    void initRandom();

    // Returns a random integer between low and high (inclusive)
    int randInRange(int low, int high);

}

#endif
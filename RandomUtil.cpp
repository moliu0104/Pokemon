#include "RandomUtil.h"

namespace util {

    // Initializes the random number generator using the current time as a seed.
    void initRandom() {
        srand(time(nullptr));
    }

    // Returns a random integer between low and high (inclusive).
    // Note: This function calls initRandom() every time, which reseeds the RNG.
    //       This can cause issues if called multiple times quickly; 
    //       Usually, initRandom() should be called **once** at program startup.
    int randInRange(int low, int high) {
        initRandom(); // Initialize random seed (should ideally be done only once)
        return low + rand() % (high - low + 1);
    }

}
#include"RandomUtil.h"

namespace util {

void initRandom() {
        srand(time(nullptr));
}

int randInRange(int low, int high) {
    initRandom();
    return low + rand() % (high - low + 1);
}

} 
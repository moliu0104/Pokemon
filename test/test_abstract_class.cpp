#include "PokemonEntity.h"

int main() {
    // This code should NOT compile!
    // Uncomment the next line to see the compile error.

    // PokemonEntity e("Test", "Type", 1, 1, 100, std::vector<Move>()); // Error: Abstract class cannot be instantiated

    // PokemonEntity* ptr = new PokemonEntity("Test", "Type", 1, 1, 100, std::vector<Move>()); // Error: same reason

    return 0;
}
#include <iostream>
#include <vector>
#include "FirePokemon.h"
#include "WaterPokemon.h"
#include "GrassPokemon.h"
#include "Move.h"
#include "PokemonEntity.h"

using namespace std;

// Test runtime polymorphism and inheritance for PokemonEntity and its derived classes
void testPolymorphism() {
    // Create sample moves for each Pokemon type
    Move ember("Ember", "Fire", 30);
    Move bubble("Bubble", "Water", 25);
    Move leaf("Leaf Blade", "Grass", 28);

    // Create vectors of moves
    vector<Move> fireMoves = {ember};
    vector<Move> waterMoves = {bubble};
    vector<Move> grassMoves = {leaf};

    // Use base class pointer to create objects of derived classes
    PokemonEntity* fire = new FirePokemon("Charmander", "Fire", 10, 1, 50, fireMoves);
    PokemonEntity* water = new WaterPokemon("Squirtle", "Water", 10, 1, 55, waterMoves);
    PokemonEntity* grass = new GrassPokemon("Bulbasaur", "Grass", 10, 1, 52, grassMoves);

    // Store all PokemonEntity pointers in a vector to test polymorphism
    vector<PokemonEntity*> team = {fire, water, grass};

    // Loop through each Pokemon in the team and test key behaviors
    for (auto p : team) {
        cout << "==== " << p->getName() << " (" << p->getType() << ") Test ====" << endl;

        // 1. Test attack: let each Pokemon attack itself to verify polymorphic attack()
        p->attack(p, p->getMoveSet()[0]);
        cout << "After attack, HP: " << p->getCurrentHP() << endl;

        // 2. Test takeDamage: deal 10 direct damage and print the result
        p->takeDamage(10);
        cout << "After takeDamage(10), HP: " << p->getCurrentHP() << endl;

        // 3. Test clone: create a deep copy and check its attributes
        PokemonEntity* clone = p->clone();
        cout << "Clone created: " << clone->getName() << ", HP: " << clone->getCurrentHP() << endl;
        delete clone; // Free memory for the clone

        cout << "-------------------------------" << endl;
    }

    // Clean up memory for all Pokemon objects
    for (auto p : team) {
        delete p;
    }
}

int main() {
    cout << "========== Polymorphism & Inheritance Test ==========" << endl;
    testPolymorphism();
    cout << "Test completed." << endl;
    return 0;
}
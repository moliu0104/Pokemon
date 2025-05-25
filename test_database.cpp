#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include "PokemonDataBase.h"
using namespace std;

int main() {
    // 1. Test file loading
    PokemonDataBase db;
    assert(!db.isEmpty() && "Database should not be empty after loading file");
    cout << "[PASS] File loaded and database is not empty." << endl;

    // 2. Test getAllPokemon
    vector<Pokemon> all = db.getAllPokemon();
    assert(all.size() > 0);
    cout << "[PASS] getAllPokemon() returns a non-empty list." << endl;

    // 3. Test findPokemonByName
    // (Assume "Bulbasaur" is in the file, modify as needed for your data)
    Pokemon* bulba = db.findPokemonByName("Bulbasaur");
    assert(bulba != nullptr && bulba->getName() == "Bulbasaur");
    cout << "[PASS] findPokemonByName('Bulbasaur') found." << endl;

    // 4. Test findPokemonByType (e.g. "Grass")
    vector<Pokemon> grasses = db.findPokemonByType("Grass");
    assert(grasses.size() > 0);
    bool foundGrass = false;
    for(auto& p : grasses) {
        if(p.getType() == "Grass") foundGrass = true;
    }
    assert(foundGrass);
    cout << "[PASS] findPokemonByType('Grass') found at least one Grass Pokemon." << endl;

    // 5. Test getRandomPokemonByType
    vector<Pokemon> chain = db.getRandomPokemonByType("Fire");
    assert(chain.size() == 3);
    for(auto& p : chain) {
        assert(p.getType() == "Fire");
    }
    cout << "[PASS] getRandomPokemonByType('Fire') returned a valid chain of 3 Fire Pokemon." << endl;

    // 6. Test addPokemon
    vector<Move> moves;
    moves.emplace_back("TestMove", "Normal", 10);
    Pokemon custom("UnitTestPoke", "Bug", 1, 99, moves);
    db.addPokemon(custom);
    Pokemon* fetched = db.findPokemonByName("UnitTestPoke");
    assert(fetched && fetched->getName() == "UnitTestPoke");
    cout << "[PASS] addPokemon() and findPokemonByName('UnitTestPoke') both working." << endl;

    cout << "All PokemonDataBase tests passed!" << endl;
    return 0;
}
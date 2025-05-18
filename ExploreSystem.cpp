#include"ExploreSystem.h"

    ExploreSystem::ExploreSystem(){
        wildPokemon = nullptr;
    }

    int ExploreSystem::run(int choice){
        clear();

        mvprintw(3, 5, "Exploring...");
        refresh();


        int times = util::randInRange(2,4);

        this_thread::sleep_for(std::chrono::seconds(times));

        string type;

        switch (choice)
        {
        case 0: type = "Grass"; break;
        case 1: type = "Water"; break;
        case 2: type = "Fire"; break;
        }

        encounterWildPokemon(type);

        choice = drawExploreMenu();
        
        endwin();

        return choice;
    }

    int ExploreSystem::drawExploreMenu(){
        clear();

        int highlight;

        vector<string> title = {"A Pokémon appeared!","-> Name: " + wildPokemon -> getName() + " | " + "Level: " + to_string(wildPokemon -> getLevel())};
        highlight = Menu::drawMenu({"Enter Battel","Run Away (Return to Map Menu)" },title,7,7,3,7);

        endwin();

        return highlight;
    }

    void ExploreSystem::encounterWildPokemon(string type){
        vector<Pokemon> pokemonChain = allPokemon.getRandomPokemonByType(type);

        int stageChance = util::randInRange(0,99);
        int stage;

        if (stageChance < 15)      stage = 3;
        else if (stageChance < 40) stage = 2;
        else                        stage = 1;

        int level = stage * 10 - util::randInRange(0,9);

        Pokemon wildSpecise;

        wildSpecise = pokemonChain[stage-1];

        if(type == "Fire"){
            wildPokemon = new FirePokemon(wildSpecise.getName(),wildSpecise.getType(),level,wildSpecise.getStage(),wildSpecise.getMaxHP(),wildSpecise.getMoveSet());
        }else if (type == "Grass")
        {
            wildPokemon = new GrassPokemon(wildSpecise.getName(),wildSpecise.getType(),level,wildSpecise.getStage(),wildSpecise.getMaxHP(),wildSpecise.getMoveSet());
        }else{
            wildPokemon = new WaterPokemon(wildSpecise.getName(),wildSpecise.getType(),level,wildSpecise.getStage(),wildSpecise.getMaxHP(),wildSpecise.getMoveSet());
        }
    }

    PokemonEntity* ExploreSystem::getWildPokemon(){
        return wildPokemon;
    }

    ExploreSystem::~ExploreSystem(){
        delete wildPokemon;
    }
#include"ExploreSystem.h"

    ExploreSystem::ExploreSystem(){
        wildPokemon = nullptr;

    }

    void ExploreSystem::run(){
        ExploreSystem self;

        vector<string> adventureTitle = {"========= Expedition Routes =========="};
        vector<string> adventureOptions = {
        "Verdale Grove",
        "Abyria Reef",
        "Emberpeak Island",
        "Exit"
        };

        int choice;

        bool running = true;
        while(running){
            clear();
            choice = Menu::drawMenu(adventureOptions,adventureTitle);
            bool ifFight = false;

            switch(MapOptions(choice)){
                case MapOptions::GrassMap:
                self.encounterWildPokemon("Grass");
                ifFight = self.tryExploring();
                break;
                
                case MapOptions::WaterMap:
                self.encounterWildPokemon("Water");
                ifFight = self.tryExploring();
                break;

                case MapOptions::FireMap:
                self.encounterWildPokemon("Fire");
                ifFight = self.tryExploring();
                break;

                case MapOptions::Exit:
                running = false;
            }

            if(ifFight){
                BattleSystem battleSystem(self.getWildPokemon());
                battleSystem.run();
            }
        }
        
        
    }

    bool ExploreSystem::tryExploring(){
        clear();
        mvprintw(3, 5, "Exploring...");
        refresh();


        int times = util::randInRange(2,4);

        this_thread::sleep_for(std::chrono::seconds(times));

        int highlight;

        vector<string> title = {"A Pokémon appeared!","-> Name: " + wildPokemon -> getName() + " | " + "Level: " + to_string(wildPokemon -> getLevel())};
        highlight = Menu::drawMenu({"Enter Battel","Run Away (Return to Map Menu)" },title,7,7,3,7);

        return !highlight;
    }

    void ExploreSystem::encounterWildPokemon(string type){
        vector<Pokemon> pokemonChain = allPokemon.getRandomPokemonByType(type);

        int stageChance = util::randInRange(0,99);
        int stage;

        if (stageChance < 10)      stage = 3;
        else if (stageChance < 30) stage = 2;
        else                        stage = 1;

        int level = stage * 10 - util::randInRange(1,10);

        if(level <= 0){
            level = 1;
        }

        Pokemon wildSpecise;

        wildSpecise = pokemonChain[stage-1];

        if (wildPokemon) { delete wildPokemon; wildPokemon = nullptr; }

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
#include"Game.h"

void Game::initGame(){
    vector<Pokemon> grassPokemon = allPokemon.getRandomPokemonByType("Grass");
    if(grassPokemon.size() > 0){
        PokemonEntity* grassPokemonEntity = new GrassPokemon(grassPokemon[0].getName(),grassPokemon[0].getType(),1,grassPokemon[0].getStage(),grassPokemon[0].getMaxHP(),grassPokemon[0].getMoveSet());
        player.addPokemonToBag(grassPokemonEntity);
    }

    player.getBag().addPotion(3);
    player.getBag().addBalls(3);
    player.addMoney(200);
}

void Game::saveGame(const string& filename) {
    ofstream fout(filename);
    fout << "MONEY " << player.getMoneyAmount() << endl;
    fout << "POTION " << player.getBag().getPotionAmount() << endl;
    fout << "BALL " << player.getBag().getBallAmount() << endl;
    for(int i = 0; i < player.getBag().getPokemonAmount(); ++i) {
        PokemonEntity* p = player.getBag().getPokemonAt(i);
        fout << "POKEMON "
             << p->getName() << " "
             << p->getType() << " "
             << p->getLevel() << " "
             << p->getStage() << " "
             << p->getMaxHP() << " "
             << p->getExp() << " "
             << "\n";
            
    }
    fout.close();
    Menu::drawMenu({"Exit"},{"Save Game Successfully!"},10,3,3,3);
}

bool Game::loadGame(const string& filename) {
    ifstream fin(filename);
    if(!fin.is_open()) return false;

    string line;
    int pokemon_count = 0;

    while(getline(fin, line)) {
    stringstream ss(line);
    string key;
    ss >> key;
    if(key == "MONEY") {
        int money;
        ss >> money;
        player.setMoneyAmount(money);
    }
    else if(key == "POTION") {
        int potions;
        ss >> potions;
        player.getBag().setPotionsAmount(potions);
    }
    else if(key == "BALL") {
        int balls;
        ss >> balls;
        player.getBag().setBallAmount(balls);
    }
    else if(key == "POKEMON") {
        string name, type;
        int level, exp, hp, maxhp, stage;
        ss >> name >> type >> level >> stage >> maxhp >> exp;
        // 1. getMoveSet要加括号
        vector<Move> moves = allPokemon.findPokemonByName(name)->getMoveSet();
        
        if(type == "Water"){
            PokemonEntity* poke = new WaterPokemon(name, type, level, stage, maxhp, exp, moves);
            player.getBag().addPokemon(poke);
        }else if(type == "Fire"){
            PokemonEntity* poke = new FirePokemon(name, type, level, stage, maxhp, exp, moves);
            player.getBag().addPokemon(poke);
        }else if(type == "Grass"){
            PokemonEntity* poke = new GrassPokemon(name, type, level, stage, maxhp, exp, moves);
            player.getBag().addPokemon(poke);
        }else{
            return false;
        }
    }
}
fin.close();
return true;
}
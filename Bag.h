#ifndef BAG_H
#define BAG_H

#include<iostream>
#include<ncurses.h>
#include<vector>
#include"Move.h"
#include"FirePokemon.h"
#include"GrassPokemon.h"
#include"WaterPokemon.h"

using namespace std;

class Bag {
private:
    int bagSize;
    int count;
    PokemonEntity** pokemons;  // 活跃宝可梦
    //std::vector<Item>   items_;      // 道具

public:
    Bag();
    // 加入一只 Pokémon，最多 6 个指针
    bool addPokemon(PokemonEntity* p);

    // 切换当前出战的 Pokémon（将第 idx 号与 0 号交换）
    bool switchActive(int index);

    // 获取当前出战 Pokémon
    PokemonEntity* getActive();

    // 打印所有 Pokémon 信息
    void printAll() ;

    // ---- 道具管理 ----
    // 添加一个道具
    //void addItem(const Item& item);

    // 使用第 idx 个道具对第 pokemonIdx 只宝可梦
    bool useItem(int idx, int pokemonIdx);

    // 打印道具列表
    void printItems(int startY = 5, int startX = 40) const;

    ~Bag();
};

#endif
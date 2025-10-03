COMMON = Pokemon.cpp PokemonDataBase.cpp PokemonEntity.cpp FirePokemon.cpp GrassPokemon.cpp WaterPokemon.cpp Move.cpp Menu.cpp ExploreSystem.cpp BattleSystem.cpp BagSystem.cpp StoreSystem.cpp RandomUtil.cpp Bag.cpp Player.cpp Game.cpp Potion.cpp PokemonBall.cpp

all: game

game: $(COMMON) main.cpp
	g++ $(COMMON) main.cpp -lncurses -o game

run_game: game
	./game

# TEST
test_pokemon_database: $(COMMON) test_pokemon_database.cpp
	g++ $(COMMON) test_pokemon_database.cpp -lncurses -o test_pokemon_database

run_test_pokemon_database: test_pokemon_database
	./test_pokemon_database

test_class_object: $(COMMON) test_class_object.cpp
	g++ $(COMMON) test_class_object.cpp -lncurses -o test_class_object

run_test_class_object: test_class_object
	./test_class_object

test_inheritance_polymorphism: $(COMMON) test_inheritance_polymorphism.cpp
	g++ $(COMMON) test_inheritance_polymorphism.cpp -lncurses -o test_inheritance_polymorphism

run_test_inheritance_polymorphism: test_inheritance_polymorphism
	./test_inheritance_polymorphism

test_abstract_class: $(COMMON) test_abstract_class.cpp
	g++ $(COMMON) test_abstract_class.cpp -lncurses -o test_abstract_class

run_test_abstract_class: test_abstract_class
	./test_abstract_class

test_bag_player: $(COMMON) test_bag_player.cpp
	g++ $(COMMON) test_bag_player.cpp -lncurses -o test_bag_player

run_test_bag_player: test_bag_player
	./test_bag_player

test_pokemon_entity: $(COMMON) test_pokemon_entity.cpp
	g++ $(COMMON) test_pokemon_entity.cpp -lncurses -o test_pokemon_entity

run_test_pokemon_entity: test_pokemon_entity
	./test_pokemon_entity

test_item: $(COMMON) test_item.cpp
	g++ $(COMMON) test_item.cpp -lncurses -o test_item

run_test_item: test_item
	./test_item

test_battle: $(COMMON) test_battle.cpp
	g++ $(COMMON) test_battle.cpp -lncurses -o test_battle

run_test_battle: test_battle
	./test_battle

test_database: $(COMMON) test_database.cpp
	g++ $(COMMON) test_database.cpp -lncurses -o test_database

run_test_database: test_database
	./test_database

test_save_load: $(COMMON) test_save_load.cpp
	g++ $(COMMON) test_save_load.cpp -lncurses -o test_save_load

run_test_save_load: test_save_load
	./test_save_load

test_user_menu: $(COMMON) test_user_menu.cpp
	g++ $(COMMON) test_user_menu.cpp -lncurses -o test_user_menu

run_test_user_menu: test_user_menu
	./test_user_menu

test_memory: $(COMMON) test_memory.cpp
	g++ $(COMMON) test_memory.cpp -lncurses -o test_memory

run_test_memory: test_memory
	./test_memory

test_boundary_cases: $(COMMON) test_boundary_cases.cpp
	g++ $(COMMON) test_boundary_cases.cpp -lncurses -o test_boundary_cases

run_test_boundary_cases: test_boundary_cases
	./test_boundary_cases

clean:
	rm -f game game test_pokemon_database test_class_object test_inheritance_polymorphism test_abstract_class test_bag_player test_pokemon_entity test_item test_battle test_database test_save_load test_user_menu test_memory test_boundary_cases
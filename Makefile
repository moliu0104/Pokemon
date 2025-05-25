game: Pokemon.cpp PokemonDataBase.cpp PokemonEntity.cpp FirePokemon.cpp GrassPokemon.cpp WaterPokemon.cpp Move.cpp Menu.cpp ExploreSystem.cpp BattleSystem.cpp BagSystem.cpp StoreSystem.cpp RandomUtil.cpp Bag.cpp Player.cpp game.cpp Potion.cpp PokemonBall.cpp main.cpp
	g++ Pokemon.cpp PokemonDataBase.cpp PokemonEntity.cpp FirePokemon.cpp GrassPokemon.cpp WaterPokemon.cpp Move.cpp Menu.cpp ExploreSystem.cpp BattleSystem.cpp BagSystem.cpp StoreSystem.cpp RandomUtil.cpp Bag.cpp Player.cpp game.cpp Potion.cpp PokemonBall.cpp main.cpp -lncurses -o game
	./game

testPokemonDataBase: Pokemon.cpp Move.cpp PokemonDataBase.cpp testPokemonDataBase.cpp
	g++ Pokemon.cpp Move.cpp PokemonDataBase.cpp testPokemonDataBase.cpp -o testPokemonDataBase
	./testPokemonDataBase

testExploreSyste:	Pokemon.cpp Move.cpp PokemonDataBase.cpp PokemonEntity.cpp Menu.cpp ExploreSystem.cpp RandomUtil.cpp Game.cpp
	g++ Pokemon.cpp Move.cpp PokemonDataBase.cpp PokemonEntity.cpp Menu.cpp ExploreSystem.cpp RandomUtil.cpp Game.cpp -lncurses -o testExploreSyste
	./testExploreSyste

clear:
	rm testPokemonDataBase testExploreSyste game
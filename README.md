# Pokémon Game 

A console-based role-playing game inspired by Pokémon, implemented in **C++** with **object-oriented programming principles** and a **ncurses-based UI**.  
This project demonstrates advanced **OOP design patterns**, **SOLID principles**, and the use of **Abstract Data Types (ADTs)** to create a modular and extensible game engine.  

---
## Description

This is a **Pokémon-inspired console game** built in **C++** with the **ncurses** library.
You can explore different maps, battle wild Pokémon, catch them, and grow your own team.
	-	Start with one Pokémon and try to catch up to 6 in your bag.
	•	Each battle gives experience and gold. Experience lets your Pokémon level up and evolve, while gold can be spent in the store.
	•	Every 150 EXP = +1 level. Every 10 levels, your Pokémon evolves to the next stage, up to Stage 3 (max level 30).
	•	Potions heal 100 HP, Poké Balls let you try to capture wild Pokémon. The lower the wild Pokémon’s HP, the higher the chance.
	•	After each victory, all your Pokémon are healed to full HP. If you lose, you gain nothing and must try again.
	•	Fire, Water, and Grass maps each have their own type of Pokémon, with type advantages and disadvantages just like the original games.
	•	You can save and load your progress (Pokémon, items, and gold).

The game is turn-based, text-based, and runs entirely in your terminal.

---

## Installation

Clone the repository:
```bash
git clone https://github.com/moliu0104/Pokemon.git
cd Pokemon
```

Build the game:
```bash
make game
```

Run the game:
```bash
./game

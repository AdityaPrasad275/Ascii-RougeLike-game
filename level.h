#ifndef ASCII_RougueLike_VISUALSTUDIO2019_ADITYA
#define ASCII_RougueLike_VISUALSTUDIO2019_ADITYA

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<conio.h>
#include<random>
#include<ctime>
#include<cstdlib>
#include<math.h>
#include<Windows.h>

class level
{

	struct player
	{
	public:
		int xPos, yPos;
		int health, damage, attackChance, defense;
		char symbol;
		std::string name;

		void init(int _xPos, int _yPos, int _health, int _damage,int _defense, int _attackChance, char _symbol, std::string _name = "player1") {
			xPos = _xPos;
			yPos = _yPos;
			health = _health;
			damage = _damage;
			defense = _defense;
			attackChance = _attackChance;
			symbol = _symbol;
			name = _name;
		}
	};

	struct monster : public player {};

	player* player1 = new player;

	void setupLevel();
	void print();
	int move();
	void monsterAi();
	void checkToMove(int _fYpos, int _fXpos, char _characterToMove, int _i = 0); // p player, m monster
	int battleSystem(monster* _monster);// 1 for won, 0 for lost , 2 for didn't fight
	std::string assignNameToMonster(monster* _monster);
	int check_if_monster_nearby(); // 0 = player dead, 1 = means continue
	void deleteAllHeapVariables();

	std::vector<monster*> monsterVec;
	std::vector<std::string> map;
	std::string levelName;

public:
	void _management(std::string _levelName);
};

#endif // !ASCII_RougueLike_VISUALSTUDIO2019_ADITYA

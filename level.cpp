#include "level.h"

void level::setupLevel()
{
	std::ifstream inputMap;
	inputMap.open(levelName);

	if (inputMap.fail()) {
		std::cout << "check the file name dumbass";
	}

	//loading the map into the vector
	std::string tempLineHolder;
	while (std::getline(inputMap, tempLineHolder)) {
		map.push_back(tempLineHolder);
	}

	//scanning the vector and initializing the player and monsters 

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j  < map[i].size(); j ++)
		{
			switch (map[i][j])
			{
			case '@':
			{
				player1->init(j, i, 100, 20, 30, 30, '@');
				break;
			}
			case 'g':
			{
				monster* goblin = new monster;
				goblin->init(j, i, 50, 30, 50, 70, 'g', "goblin");
				monsterVec.push_back(goblin);
				break;
			}
			case 'd':
			{
				monster* dragon = new monster;
				dragon->init(j, i, 1000, 70, 10, 95, 'd', "dragon");
				monsterVec.push_back(dragon);
				break;
			}
			case '#':
				break;
			case '.':
				break;
			}
		}
	}

}

void level::print()
{
	std::cout << std::string(100, '\n');

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

int level::move()
{
	switch (_getch())
	{
	case'a':
		// go left
		checkToMove(player1->yPos, player1->xPos - 1, 'p');
		return 0;
		break;
	case's':
		// go down
		checkToMove(player1->yPos + 1, player1->xPos, 'p');
		return 0;
		break;
	case'd':
		// go right
		checkToMove(player1->yPos, player1->xPos + 1, 'p');
		return 0;
		break;
	case'w':
		// go up
		checkToMove(player1->yPos - 1, player1->xPos, 'p');
		return 0;
		break;
	case 'q':
		//quit cause you're a loser
		return 1;
	default:
		std::cout << "your not hitting the right spots baby, make me cum to fill the hover dam by clicking\n"
			<< " one of these options q for quit, w for up, a for left, s for down, d for right\n";
		return move();
		break;
	}
}

void level::monsterAi()
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < monsterVec.size(); i++)
	{
		switch (1 + (rand() % 4))
		{
		case 1:
			//up
			checkToMove(monsterVec[i]->yPos - 1, monsterVec[i]->xPos, 'm', i);
			break;
		case 2:
			//down
			checkToMove(monsterVec[i]->yPos + 1, monsterVec[i]->xPos, 'm' , i);
			break;
		case 3:
			//left
			checkToMove(monsterVec[i]->yPos, monsterVec[i]->xPos - 1, 'm', i);
			break;
		case 4:
			//right
			checkToMove(monsterVec[i]->yPos, monsterVec[i]->xPos + 1, 'm', i);
			break;
		default:
			break;
		}
	}
}

void level::checkToMove(int _fYpos, int _fXpos, char _characterToMove, int _i)
{
	if (_characterToMove == 'p') {

		if (map[_fYpos][_fXpos] == '.') {
			map[player1->yPos][player1->xPos] = '.';
			map[_fYpos][_fXpos] = '@';

			player1->xPos = _fXpos;
			player1->yPos = _fYpos;
		}
		else return;

	}
	else if (_characterToMove == 'm') {

		if (map[_fYpos][_fXpos] == '.') {
			map[monsterVec[_i]->yPos][monsterVec[_i]->xPos] = '.';
			map[_fYpos][_fXpos] = monsterVec[_i]->symbol;

			monsterVec[_i]->xPos = _fXpos;
			monsterVec[_i]->yPos = _fYpos;
		}
		else return;

	}
	else return;
}

int level::battleSystem(monster* _monster)
{
	using std::cout;
	using std::cin;
	using std::endl;

	cout << "you wanna fight or run ? Answer in 1(true) and 0(false) [once the battle starts you won'r be able to run] ";
	bool wannaFight = true;
	cin >> wannaFight;

	if (wannaFight) {

		std::string monsterName = _monster->name;
		int playerAttackChance, monsterAttackChance;
		srand((unsigned)time(NULL));

		while (player1->health > 0 && _monster->health > 0) {
			
			playerAttackChance = rand() % 100 + 1;
			
			cout << "you rolled the dice\n";
			cout << "your chance of attacking is " << playerAttackChance << endl << endl;

			if (player1->attackChance <= playerAttackChance) {
				//player attacks
				_monster->health = _monster->health - (player1->damage / (_monster->defense % 10 + 1));
				
				cout << "you landed a hit !\n\n";
				Sleep(3000);

				if (_monster->health <= 0) {
					cout << monsterName << " died !! You won\n";
					Sleep(3000);
					return 1;
				}

				cout << monsterName << " health : " << _monster->health << endl;
				cout << "player health : " << player1->health << endl << endl;
				Sleep(3000);
			}
			else {
				cout << "you didn't land a hit\n\n";
				Sleep(3000);
			}

			monsterAttackChance = rand() % 100 + 1;

			cout << "the " << monsterName << " rolled the dice\n";
			cout << monsterName << "'s chance of attacking " << monsterAttackChance << endl << endl; 

			if (_monster->attackChance <= monsterAttackChance) {
				//monster attack

				player1->health = player1->health - (_monster->damage / (player1->defense % 10 + 1));
				
				cout << monsterName << "landed a hit !\n\n";
				Sleep(3000);

				if (player1->health <= 0) {
					cout << " you died !!\n";
					Sleep(3000);
					return 0;
				}

				cout << monsterName << " health : " << _monster->health << endl;
				cout << "player health : " << player1->health << endl << endl;
				Sleep(3000);
			}
			else {
				cout << monsterName << " didn't land a hit\n\n";
				Sleep(3000);
			}
		}

		if (player1->health != 0) {
			std::cout << "you won!";
			return 1;
		}
		else {
			std::cout << "you lost";
			return 0;
		}
	}
	else return 2;
}

int level::check_if_monster_nearby()
{
	bool isMonsterNearby = false;

	char tile[4] = { map[player1->xPos][player1->yPos - 1], map[player1->xPos][player1->yPos + 1], map[player1->xPos - 1][player1->yPos],map[player1->xPos + 1][player1->yPos] };
	//tile = { north, south, west, east }

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < monsterSymbols.size(); j++)
		{
			if (tile[i] == monsterSymbols[j]) {

				switch (battleSystem(monsterVec[j]))
				{
				case 0:
					map[player1->yPos][player1->xPos] = '.';
					return 0;
					break;
				case 1:
				{
					map[monsterVec[j]->yPos][monsterVec[j]->xPos] = '.';
					delete monsterVec[j];
					monsterVec[j] = NULL;

					monsterVec[j] = monsterVec.back();
					monsterVec.pop_back();

					return 1;
					break;
				}
				case 2:
					return 1;
					break;
				default:
					break;
				}
			}
		}
	}
	return 1;
}

void level::deleteAllHeapVariables()
{
	for (int i = 0; i < monsterVec.size(); i++)
	{
		delete monsterVec[i];
	}
}

void level::_management(std::string _levelName)
{
	levelName = _levelName;
	
	setupLevel();

	bool isDone = false;

	while (isDone == false) {
		
		print();
		
		monsterAi();
		
		if (move() == 1) {
			isDone = true;
			return;
		}

		if (check_if_monster_nearby() == 0) {
			isDone = true;
		}
		else isDone = false;
	}

	deleteAllHeapVariables();
	map.clear();

	int a;
	std::cin >> a;
}

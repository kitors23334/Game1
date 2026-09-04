#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"
#include <vector>

const std::vector<std::wstring> options = {
	L"Enter = choose, W = up, S = down",
	L"Continue Game",
	L"Main Menu",
	L"EXIT"
};
const std::vector<std::wstring> menu = {
	L"Enter = choose, W = up, S = down",
	L"Start game",// Difficulty level
	L"settings",
	L"EXIT"
};
const std::vector<std::wstring> Difficulty_Level = {
	L"Enter = choose, W = up, S = down, B = Return",
	L"Simple",
	L"Heavier than simple",
	L"Medium ",
	L"Lighter than heavy",
	L"Heavy ",
	L"back"
};
const std::vector<std::wstring> death = {
	L"Enter = choose, W = up, S = down",
	L"Start game",
	L"Main Menu",
	L"EXIT"
};
const std::vector<std::wstring> prenameM = {
	L"Enter = choose, W = up, S = down",
	L"No",
	L"Yes "
};


void NadoMenu(Game& game, sf::RenderWindow& window);
void NadoMenu_Start(Game& game, sf::RenderWindow& window);
void NadoMenu_Difficulty_Level(Game& game, sf::RenderWindow& window);
void NadoMenu_Settings(Game& game, sf::RenderWindow& window);
void saveGame();
bool loadGame();
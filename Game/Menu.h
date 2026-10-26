#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "GameObject.h"
#include "Game.h"
#include "physics.h"
#include <vector>

const std::vector<std::wstring> Menu = {
	L"Enter = choose, ↕ = up/down",
	L"Start game",
	L"EXIT"
};

const std::vector<std::wstring> MenuRestart = {
	L"Enter = choose, ↕ = up/down",
	L"Restart game",
	L"EXIT"
};

void NadoMenu_Start(Game& game, sf::RenderWindow& window);
void NadoMenu_Restart(GameState& state, Game& game, sf::RenderWindow& window);
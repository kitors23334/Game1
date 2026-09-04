#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Platform.h"
#include <fstream>

class GameState
{
public:
	// У меня нет динамических массивов
};

class Game
{
public:
	sf::Vector2f position;

	sf::Font font;

	Platform platform;

	sf::RectangleShape background;

	//Resources
	sf::Texture playerTexture;
	sf::Sound DeathSound;
	sf::SoundBuffer DeathSoundbuffer;

	sf::Clock PlayerCooldownf;      // таймер
	float PlayerpauseDelayf = 0.5f; // задержка
	sf::Clock pauseCooldown;      // таймер
	sf::Clock pauseCooldownf;      // таймер

	sf::Text INtext;
};

void RestartGame(Game& game);
void InitGame(Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);
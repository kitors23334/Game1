#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Platform.h"
#include "Cube.h"
#include <fstream>


class GameState {
public:
    Cube** cubes;
    int cubeCount;
    GameState(int count)
        : cubeCount(count)
    {
        cubes = new Cube * [cubeCount];
        for (int i = 0; i < cubeCount; ++i) {
            cubes[i] = new Cube();
        }
    }

    ~GameState() {
        for (int i = 0; i < cubeCount; ++i) {
            delete cubes[i];
            cubes[i] = nullptr;
        }
        delete[] cubes;
        cubes = nullptr;
    }

    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
};

class Game
{
public:
	sf::Vector2f position;

	sf::Font font;

	Platform platform;

	Cube cube;

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
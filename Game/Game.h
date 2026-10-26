#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Platform.h"
#include <fstream>


class GameState {
public:
    Cube** cubes;
    SimpleCube** simplecubes;
    int cubeCount;
    int simplecubeCount;

    GameState(int count, int simpleCount)
        : cubeCount(count)
        , simplecubeCount(simpleCount)
    {
        cubes = new Cube * [cubeCount];
        for (int i = 0; i < cubeCount; ++i) {
            cubes[i] = new Cube();
        }
        simplecubes = new SimpleCube * [simplecubeCount];
        for (int i = 0; i < simplecubeCount; ++i) {
            simplecubes[i] = new SimpleCube();
        }
    }

    ~GameState() {
        for (int i = 0; i < cubeCount; ++i) {
            delete cubes[i];
            cubes[i] = nullptr;
        }
        delete[] cubes;
        cubes = nullptr;
        for (int i = 0; i < simplecubeCount; ++i) {
            delete simplecubes[i];
            simplecubes[i] = nullptr;
        }
        delete[] simplecubes;
        simplecubes = nullptr;
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
    SimpleCube simplecube;
    Ball ball;

	sf::RectangleShape background;

	//Resources
	sf::Texture playerTexture;
	sf::Sound DeathSound;
	sf::SoundBuffer DeathSoundbuffer;

	sf::Clock PlayerCooldownf;      // таймер
	float PlayerpauseDelayf = 0.5f; // задержка
	sf::Clock pauseCooldown;      // таймер
	sf::Clock pauseCooldownf;      // таймер

};

void RestartGame(Game& game);
void InitGame(GameState& state, Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);
#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Platform.h"
#include <fstream>


class GameState {
public:
    Brick** bricks;
    DurableBrick** durablebricks;
    int cubeCount;
    int simplecubeCount;

    GameState(int count, int simpleCount)
        : cubeCount(count)
        , simplecubeCount(simpleCount)
    {
        bricks = new Brick * [cubeCount];
        for (int i = 0; i < cubeCount; ++i) {
            bricks[i] = new Brick();
        }
        durablebricks = new DurableBrick * [simplecubeCount];
        for (int i = 0; i < simplecubeCount; ++i) {
            durablebricks[i] = new DurableBrick();
        }
    }

    ~GameState() {
        for (int i = 0; i < cubeCount; ++i) {
            delete bricks[i];
            bricks[i] = nullptr;
        }
        delete[] bricks;
        bricks = nullptr;
        for (int i = 0; i < simplecubeCount; ++i) {
            delete durablebricks[i];
            durablebricks[i] = nullptr;
        }
        delete[] durablebricks;
        durablebricks = nullptr;
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
    Brick brick;
    DurableBrick durablebrick;
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
void DurableUpdateColor(DurableBrick& durablebrick);
void UpdateColor(Brick& brick);
void RestartGame(Game& game);
void InitGame(GameState& state, Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);
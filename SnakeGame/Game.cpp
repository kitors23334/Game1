#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void RestartGame(Game& game)
{
	game.StopSpawn = 0;
	game.DeathSound.setBuffer(game.DeathSoundbuffer);

	game.DeathSound.setVolume(Volume);


	InitPlayer(game.player, game);

	game.numEatenApples = 0;
	game.isGameFinished = false;
	game.timeSinceGameFinish = 0;
}

void InitGame(Game& game)
{
	InitPlayer(game.player, game);
	int seed = (int)time(nullptr);
	srand(seed);

	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
	if (!game.DeathSoundbuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav")) {
	}
	if (game.font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
	}
	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.f, 0.f);

	RestartGame(game);
}

void UpdateGame(Game& game, float deltaTime)
{
	Player player;
	if (game.isGame == true)
	{
		// Update game state
		if (!game.isGameFinished)
		{
			if (game.isGamepause == false)
			{
				if ((game.player.position.x - 70.f) <= 0.f)
				{
					game.isTouchingLeft = true;
				}
				if ((game.player.position.x + 70.f) >= 800.f)
				{
					game.isTouchingRight = true;
				}

				// Handle input
				if (game.isTouchingRight == false)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						game.player.direction = PlayerDirection::Right;
					}
				}
				if (game.isTouchingLeft == false)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						game.player.direction = PlayerDirection::Left;
					}
				}

				game.isTouchingLeft = false;
				game.isTouchingRight = false;

				// Update player state
				switch (game.player.direction)
				{
					case PlayerDirection::Right:
					{
						game.player.position.x += game.player.speed * deltaTime;
						break;
					}
					case PlayerDirection::Left:
					{
						game.player.position.x -= game.player.speed * deltaTime;
						break;
					}
				}
			}
		}
	}
}

void DrawGame(Game& game, sf::RenderWindow& window)
{
	window.draw(game.background);
	DrawPlayer(game.player, window);
}

void DeinializeGame(Game& game)
{

}
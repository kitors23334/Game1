#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void RestartGame(Game& game)
{
	game.DeathSound.setBuffer(game.DeathSoundbuffer);

	game.DeathSound.setVolume(Volume);


	InitPlatform(game.platform, game);

	game.isGameFinished = false;
	game.timeSinceGameFinish = 0;
}

void InitGame(Game& game)
{
	InitPlatform(game.platform, game);
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
	Platform platform;
	if (game.isGame == true)
	{
		// Update game state
		if (!game.isGameFinished)
		{
			if (game.isGamepause == false)
			{
				if ((game.platform.position.x - 70.f) <= 0.f)
				{
					game.isTouchingLeft = true;
				}
				if ((game.platform.position.x + 70.f) >= 800.f)
				{
					game.isTouchingRight = true;
				}

				// Handle input
				if (game.isTouchingRight == false)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						game.platform.direction = PlatformDirection::Right;
					}
				}
				if (game.isTouchingLeft == false)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						game.platform.direction = PlatformDirection::Left;
					}
				}

				game.isTouchingLeft = false;
				game.isTouchingRight = false;

				// Update player state
				switch (game.platform.direction)
				{
					case PlatformDirection::Right:
					{
						game.platform.position.x += game.platform.speed * deltaTime;
						break;
					}
					case PlatformDirection::Left:
					{
						game.platform.position.x -= game.platform.speed * deltaTime;
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
	DrawPlatform(game.platform, window);
}

void DeinializeGame(Game& game)
{

}
#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void RestartGame(Game& game)
{
	InitPlatform(game.platform, game);
	isGameFinished = false;
	timeSinceGameFinish = 0;
}

void InitGame(GameState& state, Game& game)
{
	InitPlatform(game.platform, game);
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
	if (isGameStarted == true)
	{
		if (isGameFinished == false)
		{
			// Handle input
			if (isTouchingRight == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					game.platform.direction = PlatformDirection::Right;
				}
			}
			if (isTouchingLeft == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					game.platform.direction = PlatformDirection::Left;
				}
			}
			isTouchingLeft = false;
			isTouchingRight = false;
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

void DrawGame(Game& game, sf::RenderWindow& window)
{
	window.draw(game.background);
	DrawPlatform(game.platform, window);
	DrawBall(game.ball, window);
}

void DeinializeGame(Game& game)
{

}
#include "Platform.h"
#include "Game.h"

void InitPlatform(Platform& platform, const Game& game)
{
	// Init player state
	platform.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f };
	platform.direction = PlatformDirection::Stop;

	// init player sprite
	platform.PlatformOb.setSize(sf::Vector2f(100.f, 20.f));
	platform.PlatformOb.setOrigin(platform.PlatformOb.getSize() / 2.f);
	platform.PlatformOb.setFillColor(sf::Color::White);
}

void DrawPlatform(Platform& platform, sf::RenderWindow& window)
{
	platform.PlatformOb.setPosition(platform.position.x, platform.position.y);
	window.draw(platform.PlatformOb);
}
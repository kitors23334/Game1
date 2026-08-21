#include "Player.h"
#include "Game.h"

void InitPlayer(Player& player, const Game& game)
{
	// Init player state
	player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f };
	player.direction = PlayerDirection::Stop;

	// init player sprite
	player.playerOb.setSize(sf::Vector2f(100.f, 20.f));
	player.playerOb.setOrigin(player.playerOb.getSize() / 2.f);
	player.playerOb.setFillColor(sf::Color::White);
}

void DrawPlayer(Player& player, sf::RenderWindow& window)
{
	player.playerOb.setPosition(player.position.x, player.position.y);
	window.draw(player.playerOb);
}
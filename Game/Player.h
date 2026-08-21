#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

enum class PlayerDirection
{
	Right = 0,
	Up,
	Left,
	Down
};

struct Player
{
	Position2D position;
	PlayerDirection direction = PlayerDirection::Right;
	sf::Sprite sprite;
};

struct Back1
{
	Position2D position;
	sf::Sprite BackSprite;
};

struct TailSegment {
	sf::Vector2f pos;       // Позиция центра или угла сегмента
	PlayerDirection dir;    // Направление, в котором этот сегмент "смотрит"
};

struct Game;

void InitPlayer(Player& player, const Game& game);
void DrawPlayer(Player& player, sf::RenderWindow& window);

void playerDown(Player& player);
void playerLeft(Player& player);
void playerUp(Player& player);
void playerRight(Player& player);

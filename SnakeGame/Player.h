#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

enum class PlayerDirection
{
	Stop = 0,
	Right,
	Left,
};

class Player
{
public:
	Position2D position;
	float speed = 500;
	PlayerDirection direction = PlayerDirection::Right;
	sf::RectangleShape playerOb;
};

struct Game;
void InitPlayer(Player& player, const Game& game);
void DrawPlayer(Player& player, sf::RenderWindow& window);

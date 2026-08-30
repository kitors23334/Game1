#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

enum class PlatformDirection
{
	Stop = 0,
	Right,
	Left,
};

class Platform
{
public:
	Position2D position;
	float speed = 500;
	PlatformDirection direction = PlatformDirection::Right;
	sf::RectangleShape PlatformOb;
};

struct Game;
void InitPlatform(Platform& platform, const Game& game);
void DrawPlatform(Platform& platform, sf::RenderWindow& window);

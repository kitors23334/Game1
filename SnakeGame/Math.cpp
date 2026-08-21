#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Game.h"

Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
{
    Game game;
    int cellsX = static_cast<int>(screenWidth / Size_Kletko);
    int cellsY = static_cast<int>(screenHeight / Size_Kletko);

    if (cellsX <= 0 || cellsY <= 0) {
        return Position2D{ 0.f, 0.f };
    }

    int safeTopRows = 0;

    if (safeTopRows >= cellsY) {
        safeTopRows = 1;
    }

    int maxAttempts = cellsX * cellsY * 2;
    int attempts = 0;

    Position2D result;

    do {
        int randomCellX = std::rand() % cellsX;

        int randomCellY = (std::rand() % (cellsY - safeTopRows)) + safeTopRows;

        result.x = (randomCellX * Size_Kletko) + (Size_Kletko / 2.0f);
        result.y = (randomCellY * Size_Kletko) + (Size_Kletko / 1.1f);

        bool isOccupied = false;

        attempts++;

        if (!isOccupied || attempts >= maxAttempts) {
            break;
        }

    } while (true);

    if (attempts >= maxAttempts) {
        return Position2D{ 0.f, 0.f };
    }

    return result;
}

bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
{
	float dx = (float)fabs(rect1Position.x - rect2Position.x);
	float dy = (float)fabs(rect1Position.y - rect2Position.y);
	return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
		dy <= (rect1Size.y + rect2Size.y) / 2.f);
}

bool IsCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
{
	float squareDistance = (circle1Position.x - circle2Position.x) *
		(circle1Position.x - circle2Position.x) +
		(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
	float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
	return squareDistance <= squareRadiusSum;
}

void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
{
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
	sprite.setScale(scale);
}

void setSpriteOrigin(sf::Sprite& sprite, float originX, float originY)
{
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
}
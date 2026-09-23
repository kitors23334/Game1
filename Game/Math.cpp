#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Game.h"


Position2D GetRandomPositionInScreen(
    float screenWidth, float screenHeight,
    const std::vector<Position2D>& occupied,
    float cubeSize
) {
    const float bottomMargin = 160.f;   // отступ снизу
    const float edgeMargin = 20.f;     // отступ от левого/правого/верхнего края

    float minX = edgeMargin + cubeSize / 2.f;
    float maxX = screenWidth - edgeMargin - cubeSize / 2.f;

    float minY = edgeMargin + cubeSize / 2.f;
    float maxY = screenHeight - bottomMargin - cubeSize / 2.f;

    if (minX >= maxX) minX = 0.f, maxX = screenWidth - cubeSize;
    if (minY >= maxY) minY = 0.f, maxY = screenHeight - bottomMargin - cubeSize;

    int rangeX = static_cast<int>(maxX - minX);
    int rangeY = static_cast<int>(maxY - minY);

    if (rangeX <= 0) rangeX = 1;
    if (rangeY <= 0) rangeY = 1;

    const int maxAttempts = 500;
    for (int i = 0; i < maxAttempts; ++i) {
        float x = minX + static_cast<float>(rand() % rangeX);
        float y = minY + static_cast<float>(rand() % rangeY);

        bool isFree = true;
        for (const auto& p : occupied) {
            float dx = x - p.x;
            float dy = y - p.y;
            if (dx * dx + dy * dy < (cubeSize * cubeSize)) {
                isFree = false;
                break;
            }
        }

        if (isFree) {
            return Position2D{ x, y };
        }
    }

    return Position2D{ (screenWidth - cubeSize) / 2.f, (screenHeight - bottomMargin - cubeSize) / 2.f };
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
#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Constants.h"
#include "Math.h"
#include <algorithm>
#include <cmath>


class GameObject
{
protected:

public:

};

class Ball : public GameObject {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float ballSpeedX = 1.2f * 250;
    float ballSpeedY = 1.1f * 250;
    float BallRadius = 15.f;
    sf::CircleShape BallOb;
};

struct Game;
void InitBall(Ball& ball, const Game& game);
void DrawBall(Ball& ball, sf::RenderWindow& window);

class Brick : public GameObject {
public:
    Position2D position;
    sf::RectangleShape BrickOb;
    bool isActive = true;

    int hitPoints = 1;
    int hitCount = 0;
};

class DurableBrick : public Brick {
public:
    Position2D position;
    sf::RectangleShape DurableBrickOb;
    bool isActive = true;

    int hitPoints = 3;
    int hitCount = 0;
};

struct Game;
void InitBall(Ball& ball, const Game& game);
void DrawBall(Ball& ball, sf::RenderWindow& window);

void InitBrick(Brick& brick, Game& game);
void DrawBrick(Brick& brick, sf::RenderWindow& window);

void InitDurableBrick(DurableBrick& durablebrick, Game& game);
void DrawDurableBrick(DurableBrick& durablebrick, sf::RenderWindow& window);
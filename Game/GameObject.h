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

class Cube : public GameObject {
public:
    Position2D position;
    sf::RectangleShape CubeOb;
    bool isActive = true;

    int maxBounces = 1;      // сколько надо отскоков
    int bounceCount = 0;     // сколько уже отскоков

    Cube() {
        CubeOb.setSize(sf::Vector2f(40.f, 40.f));
        CubeOb.setOrigin(CubeOb.getSize() / 2.f);
        UpdateColor();
    }

    void UpdateColor() {
        int remaining = maxBounces - bounceCount;
        if (remaining >= 3)
            CubeOb.setFillColor(sf::Color::Yellow);
        else if (remaining == 2)
            CubeOb.setFillColor(sf::Color::Blue);
        else
            CubeOb.setFillColor(sf::Color::Green);
    }
};

class SimpleCube : public Cube {
public:
    Position2D position;
    sf::RectangleShape SimpleCubeOb;
    bool isActive = true;

    int maxBounces = 3;      // сколько надо отскоков "rand() % 2 + 2"
    int bounceCount = 0;     // сколько уже отскоков

    SimpleCube() {
        SimpleCubeOb.setSize(sf::Vector2f(40.f, 40.f));
        SimpleCubeOb.setOrigin(SimpleCubeOb.getSize() / 2.f);
        UpdateColor();
    }

    void UpdateColor() {
        int remaining = maxBounces - bounceCount;
        if (remaining >= 3)
            SimpleCubeOb.setFillColor(sf::Color::Yellow);
        else if (remaining == 2)
            SimpleCubeOb.setFillColor(sf::Color::Blue);
        else
            SimpleCubeOb.setFillColor(sf::Color::Green);
    }
};

struct Game;
void InitBall(Ball& ball, const Game& game);
void DrawBall(Ball& ball, sf::RenderWindow& window);

void InitCube(Cube& cube, Game& game);
void DrawCube(Cube& cube, sf::RenderWindow& window);

void InitSimpleCube(SimpleCube& simplecube, Game& game);
void DrawSimpleCube(SimpleCube& simplecube, sf::RenderWindow& window);
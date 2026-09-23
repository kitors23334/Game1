#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Math.h"

class Cube : public GameObject {
public:
    Position2D position;
    sf::RectangleShape CubeOb;
    bool active = true;
    Cube() {
        CubeOb.setSize(sf::Vector2f(40.f, 40.f));
        CubeOb.setOrigin(CubeOb.getSize() / 2.f);
        CubeOb.setFillColor(sf::Color::Green);
    }
};

struct Game;
void InitCube(Cube& cube, Game& game);
void DrawCube(Cube& cube, sf::RenderWindow& window);
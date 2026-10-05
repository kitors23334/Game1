#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Math.h"

class Cube : public GameObject {
public:
    Position2D position;
    sf::RectangleShape CubeOb;
    bool active = true;
    int CountRegN = rand() % 3 + 1;
    int CountReg = 0;
    Cube() {
        CubeOb.setSize(sf::Vector2f(40.f, 40.f));
        CubeOb.setOrigin(CubeOb.getSize() / 2.f);
        UpdateColor();
    }
    void UpdateColor() {

        if ((CountRegN - CountReg) >= 3)
            CubeOb.setFillColor(sf::Color::Yellow);
        else if ((CountRegN - CountReg) == 2)
            CubeOb.setFillColor(sf::Color::Blue);
        else
            CubeOb.setFillColor(sf::Color::Green);
    }
};

struct Game;
void InitCube(Cube& cube, Game& game);
void DrawCube(Cube& cube, sf::RenderWindow& window);
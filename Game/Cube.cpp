#include "Cube.h"
#include "Game.h"

void InitCube(Cube& cube, Game& game) {
    float minX = 20.f;
    float maxX = static_cast<float>(SCREEN_WIDTH) - 20.f;
    float minY = 20.f;
    float maxY = static_cast<float>(SCREEN_HEIGHT) - 100.f;

    cube.position.x = minX + static_cast<float>(rand() % static_cast<int>(maxX - minX));
    cube.position.y = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY));

    cube.CubeOb.setSize(sf::Vector2f(40.f, 40.f));
    cube.CubeOb.setOrigin(cube.CubeOb.getSize() / 2.f);
    cube.CubeOb.setFillColor(sf::Color::Green);
}

void DrawCube(Cube& cube, sf::RenderWindow& window) {
    if (!cube.active)
        return;

    cube.CubeOb.setPosition(cube.position.x, cube.position.y);
    window.draw(cube.CubeOb);
}

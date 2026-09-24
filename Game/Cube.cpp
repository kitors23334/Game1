#include "Cube.h"
#include "Game.h"

void InitCube(Cube& cube, Game& game) {
    Position2D randomPos = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    cube.position.x = randomPos.x;
    cube.position.y = randomPos.y;

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

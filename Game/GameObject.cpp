#include "GameObject.h"
#include "Game.h"

void InitBall(Ball& ball, const Game& game)
{
    // Init player state
    ball.position = { SCREEN_WIDTH / 2.f, 100 };

    // init player sprite
    ball.BallOb.setRadius(ball.BallRadius);
    ball.BallOb.setOrigin(ball.BallOb.getRadius(), ball.BallOb.getRadius());
    ball.BallOb.setFillColor(sf::Color::Red);
}

void DrawBall(Ball& ball, sf::RenderWindow& window)
{
    ball.BallOb.setPosition(ball.position.x, ball.position.y);
    window.draw(ball.BallOb);
}

void InitCube(Cube& cube, Game& game) {
    Position2D randomPos = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    cube.position.x = randomPos.x;
    cube.position.y = randomPos.y;

    cube.CubeOb.setSize(sf::Vector2f(40.f, 40.f));
    cube.CubeOb.setOrigin(cube.CubeOb.getSize() / 2.f);
    void UpdateColor();
}

void DrawCube(Cube& cube, sf::RenderWindow& window) {
    cube.CubeOb.setPosition(cube.position.x, cube.position.y);
    window.draw(cube.CubeOb);
}

void InitSimpleCube(SimpleCube& simplecube, Game& game) {
    Position2D simplerandomPos = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    simplecube.position.x = simplerandomPos.x;
    simplecube.position.y = simplerandomPos.y;

    simplecube.SimpleCubeOb.setSize(sf::Vector2f(40.f, 40.f));
    simplecube.SimpleCubeOb.setOrigin(simplecube.SimpleCubeOb.getSize() / 2.f);
    void UpdateColor();
}

void DrawSimpleCube(SimpleCube& simplecube, sf::RenderWindow& window) {
    simplecube.SimpleCubeOb.setPosition(simplecube.position.x, simplecube.position.y);
    window.draw(simplecube.SimpleCubeOb);
}

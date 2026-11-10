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

void InitBrick(Brick& brick, Game& game) {
    Position2D randomPos = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    brick.position.x = randomPos.x;
    brick.position.y = randomPos.y;

    brick.BrickOb.setSize(sf::Vector2f(40.f, 40.f));
    brick.BrickOb.setOrigin(brick.BrickOb.getSize() / 2.f);
    void UpdateColor();
}

void DrawBrick(Brick& brick, sf::RenderWindow& window) {
    brick.BrickOb.setPosition(brick.position.x, brick.position.y);
    window.draw(brick.BrickOb);
}

void InitDurableBrick(DurableBrick& durablebrick, Game& game) {
    Position2D simplerandomPos = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

    durablebrick.position.x = simplerandomPos.x;
    durablebrick.position.y = simplerandomPos.y;

    durablebrick.DurableBrickOb.setSize(sf::Vector2f(40.f, 40.f));
    durablebrick.DurableBrickOb.setOrigin(durablebrick.DurableBrickOb.getSize() / 2.f);
    void UpdateColor();
}

void DrawDurableBrick(DurableBrick& durablebrick, sf::RenderWindow& window) {
    durablebrick.DurableBrickOb.setPosition(durablebrick.position.x, durablebrick.position.y);
    window.draw(durablebrick.DurableBrickOb);
}


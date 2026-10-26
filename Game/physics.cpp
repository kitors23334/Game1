#include "game.h"
#include <algorithm>
#include <cmath>

void UpdateBallWithWalls(Ball& ball, float dt)
{
    ball.position.x += ball.ballSpeedX * dt;
    ball.position.y += ball.ballSpeedY * dt;

    // Левая и правая
    if (ball.position.x - ball.BallRadius <= 0.f) {
        ball.position.x = ball.BallRadius;
        ball.ballSpeedX *= -1.f;
    }
    else if (ball.position.x + ball.BallRadius >= SCREEN_WIDTH) {
        ball.position.x = SCREEN_WIDTH - ball.BallRadius;
        ball.ballSpeedX *= -1.f;
    }

    // Верхняя и нижняя
    if (ball.position.y - ball.BallRadius <= 0.f) {
        ball.position.y = ball.BallRadius;
        ball.ballSpeedY *= -1.f;
    }
    else if (ball.position.y + ball.BallRadius >= SCREEN_HEIGHT) {
        ball.position.y = SCREEN_HEIGHT - ball.BallRadius;
        ball.ballSpeedY *= -1.f;
    }
}

bool CheckBallPlatformCollision(const Ball& ball, const Platform& platform)
{
    float px = platform.position.x;
    float py = platform.position.y;
    float pw = platform.PlatformOb.getSize().x;
    float ph = platform.PlatformOb.getSize().y;

    float closestX = std::max(px - pw / 2.f, std::min(ball.position.x, px + pw / 2.f));
    float closestY = std::max(py - ph / 2.f, std::min(ball.position.y, py + ph / 2.f));

    float dx = ball.position.x - closestX;
    float dy = ball.position.y - closestY;

    return (dx * dx + dy * dy) <= ball.BallRadius * ball.BallRadius;
}

void HandleBallPlatformBounce(Ball& ball, const Platform& platform)
{
    float px = platform.position.x;
    float py = platform.position.y;
    float pw = platform.PlatformOb.getSize().x;
    float ph = platform.PlatformOb.getSize().y;

    float closestX = std::max(px - pw / 2.f, std::min(ball.position.x, px + pw / 2.f));
    float closestY = std::max(py - ph / 2.f, std::min(ball.position.y, py + ph / 2.f));

    float dx = ball.position.x - closestX;
    float dy = ball.position.y - closestY;

    if (std::abs(dx) < std::abs(dy)) {
        // сверху или снизу
        ball.ballSpeedY *= -1.f;
        if (ball.position.y < py)
            ball.position.y = closestY - ball.BallRadius;
        else
            ball.position.y = closestY + ball.BallRadius;
    }
    else {
        // слева или справа
        ball.ballSpeedX *= -1.f;
        if (ball.position.x < px)
            ball.position.x = closestX - ball.BallRadius;
        else
            ball.position.x = closestX + ball.BallRadius;
    }
}

bool HandleBallCubeBounce(Ball& ball, Cube& cube) {
    if (!cube.isActive) return false;

    float cx = cube.position.x;
    float cy = cube.position.y;
    float cw = cube.CubeOb.getSize().x;
    float ch = cube.CubeOb.getSize().y;

    float closestX = std::max(cx - cw / 2.f, std::min(ball.position.x, cx + cw / 2.f));
    float closestY = std::max(cy - ch / 2.f, std::min(ball.position.y, cy + ch / 2.f));

    float dx = ball.position.x - closestX;
    float dy = ball.position.y - closestY;

    float distSq = dx * dx + dy * dy;
    float radius = ball.BallRadius;

    // Если нет столкновения
    if (distSq > radius * radius) {
        return false;
    }

    if (cube.bounceCount > 0 && distSq < 0.1f) {
        return false;
    }

    cube.bounceCount++;
    score += 1;
    cube.UpdateColor();

    if (std::abs(dx) < std::abs(dy)) {
        // сверху снизу
        ball.ballSpeedY *= -1.f;
        if (ball.position.y < cy)
            ball.position.y = closestY - radius;
        else
            ball.position.y = closestY + radius;
    }
    else {
        // слева справа
        ball.ballSpeedX *= -1.f;
        if (ball.position.x < cx)
            ball.position.x = closestX - radius;
        else
            ball.position.x = closestX + radius;
    }

    return (cube.bounceCount >= cube.maxBounces);
}

// 2
bool HandleBallSimpleCubeBounce(Ball& ball, SimpleCube& simplecube) {
    if (!simplecube.isActive) return false;

    float scx = simplecube.position.x;
    float scy = simplecube.position.y;
    float scw = simplecube.SimpleCubeOb.getSize().x;
    float sch = simplecube.SimpleCubeOb.getSize().y;

    float closestX = std::max(scx - scw / 2.f, std::min(ball.position.x, scx + scw / 2.f));
    float closestY = std::max(scy - sch / 2.f, std::min(ball.position.y, scy + sch / 2.f));

    float sdx = ball.position.x - closestX;
    float sdy = ball.position.y - closestY;

    float distSq = sdx * sdx + sdy * sdy;
    float radius = ball.BallRadius;

    // Если нет столкновения
    if (distSq > radius * radius) {
        return false;
    }

    if (simplecube.bounceCount > 0 && distSq < 0.1f) {
        return false;
    }

    simplecube.bounceCount++;
    score += 1;
    simplecube.UpdateColor();

    if (std::abs(sdx) < std::abs(sdy)) {
        // сверху снизу
        ball.ballSpeedY *= -1.f;
        if (ball.position.y < scy)
            ball.position.y = closestY - radius;
        else
            ball.position.y = closestY + radius;
    }
    else {
        // слева справа
        ball.ballSpeedX *= -1.f;
        if (ball.position.x < scx)
            ball.position.x = closestX - radius;
        else
            ball.position.x = closestX + radius;
    }

    return (simplecube.bounceCount >= simplecube.maxBounces);
}

void resetBall(Ball& ball, GameState& game, float startSpeedX, float startSpeedY) {
    ball.position.x = SCREEN_WIDTH / 2.0f;
    ball.position.y = SCREEN_HEIGHT / 2.0f;

    ball.velocity.x = startSpeedX;
    ball.velocity.y = startSpeedY;

}
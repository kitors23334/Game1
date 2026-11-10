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

bool HandleBallBrickBounce(Ball& ball, Brick& brick) {
    if (!brick.isActive) return false;

    float cx = brick.position.x;
    float cy = brick.position.y;
    float cw = brick.BrickOb.getSize().x;
    float ch = brick.BrickOb.getSize().y;

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

    if (brick.hitCount > 0 && distSq < 0.1f) {
        return false;
    }

    brick.hitCount++;
    score += 1;
    UpdateColor(brick);

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

    return (brick.hitCount >= brick.hitPoints);
}

// 2
bool HandleBallDurableBrickBounce(Ball& ball, DurableBrick& durablebrick) {
    if (!durablebrick.isActive) return false;

    float scx = durablebrick.position.x;
    float scy = durablebrick.position.y;
    float scw = durablebrick.DurableBrickOb.getSize().x;
    float sch = durablebrick.DurableBrickOb.getSize().y;

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

    if (durablebrick.hitCount > 0 && distSq < 0.1f) {
        return false;
    }

    durablebrick.hitCount++;
    score += 1;
    DurableUpdateColor(durablebrick);

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

    return (durablebrick.hitCount >= durablebrick.hitPoints);
}

void resetBall(Ball& ball, GameState& game, float startSpeedX, float startSpeedY) {
    ball.position.x = SCREEN_WIDTH / 2.0f;
    ball.position.y = SCREEN_HEIGHT / 2.0f;

    ball.velocity.x = startSpeedX;
    ball.velocity.y = startSpeedY;

}
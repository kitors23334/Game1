#pragma once
#include "Platform.h"
#include "physics.h"
#include <cmath>
#include "Game.h"
#include <algorithm>

void HandleBallPlatformBounce(Ball& ball, const Platform& platform);
bool CheckBallPlatformCollision(const Ball& ball, const Platform& platform);
void UpdateBallWithWalls(Ball& ball, float dt);
bool HandleBallBrickBounce(Ball& ball, Brick& brick);
bool HandleBallDurableBrickBounce(Ball& ball, DurableBrick& durablebrick);
void resetBall(Ball& ball, GameState& game, float startSpeedX, float startSpeedY);
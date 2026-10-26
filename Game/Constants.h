#pragma once
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float ballRadius = 15.f;
const float itemHeight = 32.f;
const float startY = 200.f;
const float pauseDelay = 1.0f; // задержка
const float pauseDelayf = 0.2f; // задержка

// import
extern int selectedIndex;
extern int score;
extern bool Menu_Start;
extern bool Menu_Restart;
extern bool isGameFinished;
extern bool isGameStarted;
extern bool isTouchingLeft;
extern bool isTouchingRight;
extern float timeSinceGameFinish;
#pragma once
#include <iostream>
#include <string>
#include "constants.h"

// edit
std::string inputText;

int selectedIndex = 0;
int score = 0;

bool Menu_Start = true;
bool Menu_Restart = false;

bool isGameFinished = false;
bool isGameStarted = false;

bool isTouchingLeft = false;
bool isTouchingRight = false;

float timeSinceGameFinish = 0.f;
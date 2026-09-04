#pragma once
#include <iostream>
#include <string>
#include "constants.h"

// edit
std::string inputText;

int NUM_APPLES = 100;
int Volume = 50;

int selectedIndex = 0;
int Precount = 0;

bool Menu_Start = true;
bool Menu_Difficulty_Level = false;
bool Menu_Leader_Board = false;
bool Menu_Settings = false;
bool music = true;
bool sounds = true;

bool isGameFinished = false;
bool isGame = false;
bool nadoname = true;
bool prename = true;
bool name = false;
bool isGamepause = false;

bool isTouchingLeft = false;
bool isTouchingRight = false;

float timeSinceGameFinish = 0.f;

std::string music_stext = "music<=";
std::string sounds_stext = "sounds<=";
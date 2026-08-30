#pragma once
#include <string>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float Size_Kletko = 38.f;
const float PLAYER_SIZE = 38.f;
const float APPLE_SIZE = 35.f;
const float PAUSE_LENGTH = 3.f;
const float ballRadius = 15.f;
extern int Volume;
const int Const_NUM_APPLES = 100;
extern int NUM_APPLES;
extern bool Menu_Start;
extern bool Menu_Difficulty_Level;
extern bool Menu_Leader_Board;
extern bool Menu_Settings;
extern std::string music_stext;
extern std::string sounds_stext;
extern bool music;
extern bool sounds;

enum GameMode 
{
    MODE_NONE = 0,
    MODE_1 = 1 << 0,
    MODE_2 = 1 << 1,
    MODE_3 = 1 << 2,
    MODE_4 = 1 << 3,
    MODE_5 = 1 << 4,
    MODE_6 = 1 << 5,
    MODE_7 = 1 << 6,
    MODE_8 = 1 << 7
};
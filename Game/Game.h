#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Platform.h"
#include <fstream>

class GameState
{
public:
	// У меня нет динамических массивов
};


class Game
{
private:
	const std::string SAVE_FILE = "save.txt";
public:
	sf::Vector2f position;

	sf::Font font;

	Platform platform;

	// Global game data
	std::string inputText;
	float timeSinceGameFinish = 0.f;
	float PlayerSize = 0.72f;
	const float itemHeight = 32.f;
	const float startY = 200.f;
	int selectedIndex = 0;
	int Precount = 0;
	bool isGameFinished = false;
	bool isGame = false;
	bool nadoname = true;
	bool prename = true;
	bool name = false;
	bool isGamepause = false;

	bool isTouchingLeft = false;
	bool isTouchingRight = false;

	sf::RectangleShape background;

	//Resources
	sf::Texture playerTexture;
	sf::Sound DeathSound;
	sf::SoundBuffer DeathSoundbuffer;

	sf::Clock PlayerCooldownf;      // таймер
	float PlayerpauseDelayf = 0.5f; // задержка
	sf::Clock pauseCooldown;      // таймер
	const float pauseDelay = 1.0f; // задержка
	sf::Clock pauseCooldownf;      // таймер
	const float pauseDelayf = 0.2f; // задержка

	sf::Text INtext;

	void saveGame()
	{
		std::ofstream out(SAVE_FILE);
		if (!out.is_open()) {
			// лучше логировать ошибку, а не просто return
			return;
		}

		// Порядок записи должен совпадать с порядком чтения в loadGame()
		out << (sounds ? 1 : 0) << "\n";
		out << (nadoname ? 1 : 0) << "\n";
		out << (music ? 1 : 0) << "\n";
		// Для строки лучше писать длину + строку или использовать getline; простой вариант:
		out << inputText << "\n";
	}

	bool loadGame()
	{
		std::ifstream in(SAVE_FILE);
		if (!in.is_open())
			return false;

		int savedInt;

		if (!(in >> savedInt)) return false;
		sounds = (savedInt != 0);
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (!(in >> savedInt)) return false;
		nadoname = (savedInt != 0);
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (!(in >> savedInt)) return false;
		music = (savedInt != 0);
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// getline читает остаток текущей строки (если после последнего числа есть перевод строки),
		// поэтому перед ним нужен ignore, либо читай строку отдельно.
		if (!std::getline(in, inputText)) {
			inputText.clear(); // если строка не прочиталась, лучше явно очистить
			return false;
		}

		return true;
	}
};

void RestartGame(Game& game);
void InitGame(Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);
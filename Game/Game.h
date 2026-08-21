#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include <fstream>

struct Game
{
	sf::Vector2f position;

	const std::string SAVE_FILE = "save.txt";
	Back1 back1;

	sf::Font font;

	Player player;
	Apple* apples = new Apple[NUM_APPLES];

	std::vector<TailSegment> tailSegments;         // пустой вектор позиций

	// Global game data
	std::string inputText;
	float timeSinceGameFinish = 0.f;
	const float itemHeight = 32.f;
	const float startY = 200.f;
	int count = 0;
	float segmentSize = 0.75f;
	int initialLength = 0;
	int selectedIndex = 0;
	int Precount = 0;
	int numEatenApples = 0;
	int MaxNumEatenApples = 0;
	int maxTailLength = 0;
	bool isGameFinished = false;
	bool isGame = false;
	bool nadoname = true;
	bool prename = true;
	bool name = false;
	bool Bsnake = false;
	bool isGamepause = false;
	bool StopSpawn = false;

	sf::RectangleShape background;

	//Resources
	sf::Texture BackTexture;
	sf::Texture playerTexture;
	sf::Texture AppleTexture;
	sf::Sound DeathSound;
	sf::Sound AppleEatSound;
	sf::SoundBuffer AppleEatbuffer;
	sf::SoundBuffer DeathSoundbuffer;
	// Головы
	sf::Texture HeadUp;
	sf::Texture HeadDown;
	sf::Texture HeadLeft;
	sf::Texture HeadRight;

	// Тело (прямые участки)
	sf::Texture BodyLR; // Left-Right (горизонтальное)
	sf::Texture BodyUD; // Down-Up (вертикальное)

	// Повороты (углы)
	sf::Texture TurnLU; // Left-Up
	sf::Texture TurnLD; // Left-Down
	sf::Texture TurnRU; // Right-Up
	sf::Texture TurnDR; // Down-Right (или Down-Rigth, проверь имя файла)

	// Хвосты
	sf::Texture TailUp;
	sf::Texture TailDown;
	sf::Texture TailLeft;
	sf::Texture TailRight;

	sf::Sprite HeadUpSprite;
	sf::Sprite HeadDownSprite;
	sf::Sprite HeadLeftSprite;
	sf::Sprite HeadRightSprite;

	sf::Sprite BodyLRSprite;
	sf::Sprite BodyUDSprite;

	sf::Sprite TurnLUSprite;
	sf::Sprite TurnLDSprite;
	sf::Sprite TurnRUSprite;
	sf::Sprite TurnDRSprite;

	sf::Sprite TailUpSprite;
	sf::Sprite TailDownSprite;
	sf::Sprite TailLeftSprite;
	sf::Sprite TailRightSprite;


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
		out << MaxNumEatenApples << "\n";
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

		if (!(in >> MaxNumEatenApples)) return false;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропустить остаток строки после числа

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

void RestartGame(Back1& back1, Game& game);
void InitGame(Game& game);
void UpdateGame(Game& game, float deltaTime);
void DrawGame(Back1& back1, Game& game, sf::RenderWindow& window);
void DeinializeGame(Game& game);
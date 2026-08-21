// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"

struct PlayerScore
{
	std::string name;
	int score;
};

void sortLeaderboard(std::vector<PlayerScore>& board)
{

	size_t n = board.size();
	for (size_t i = 0; i < n - 1; ++i) {
		bool swapped = false;
		for (size_t j = 0; j < n - i - 1; ++j) {
			if (board[j].score < board[j + 1].score) { // по убыванию
				std::swap(board[j], board[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break; // оптимизация: если перестановок не было — массив уже отсортирован
	}
}

int main()
{
	Game game;
	game.inputText = "you";
	// 1. При старте — пытаемся загрузить
	game.loadGame(); 

	game.INtext.setFont(game.font);
	game.INtext.setString(game.inputText);
	game.INtext.setFillColor(sf::Color::White);
	game.INtext.setCharacterSize(24);
	game.INtext.setPosition(SCREEN_WIDTH - 570, SCREEN_HEIGHT - 350); // слева сверху

	// Текст для надписи "Score"
	sf::Text scoreLabel("Score:", game.font, 15);
	scoreLabel.setFillColor(sf::Color::White);
	scoreLabel.setPosition(10.f, -3.f); // слева сверху

	// Текст для значения счёта
	sf::Text scoreValue("", game.font, 15);
	scoreValue.setFillColor(sf::Color::Yellow);
	scoreValue.setPosition(56.f, -3.f); // чуть ниже надписи "Score"

	// Текст для надписи "Score"
	sf::Text scoreLabel2("MaxScore:", game.font, 15);
	scoreLabel2.setFillColor(sf::Color::White);
	scoreLabel2.setPosition(90.f, -3.f); // слева сверху

	// Текст для значения счёта
	sf::Text scoreValue2("", game.font, 15);
	scoreValue2.setFillColor(sf::Color::Yellow);
	scoreValue2.setPosition(165.f, -3.f); // чуть ниже надписи "Score"

	int seed = static_cast<int>(time(nullptr));
	srand(seed);

	int Alice = (std::rand() % (200 - 1 + 1)) + 1;
	int Bob = (std::rand() % (200 - 1 + 1)) + 1;
	int Carol = (std::rand() % (200 - 1 + 1)) + 1;
	int Dave = (std::rand() % (200 - 1 + 1)) + 1;
	int Eve = (std::rand() % (200 - 1 + 1)) + 1;

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	InitGame(game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		if (sounds == true) {
			sounds_stext = "sounds<=";
		}
		if (sounds == false) {
			sounds_stext = "sounds";
		}
		if (music == true) {
			music_stext = "music<=";
		}
		if (music == false) {
			music_stext = "music";
		}
		scoreValue.setString(std::to_string(game.numEatenApples));
		scoreValue2.setString(std::to_string(game.MaxNumEatenApples));

		// Calculate time delta
		std::vector<PlayerScore> leaderboard =
		{
			{game.inputText,  game.numEatenApples},
			{"Alice",  Alice},
			{"Bob",     Bob},
			{"Carol",   Carol},
			{"Dave",    Dave},
			{"Eve",     Eve}
		};

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			std::vector<PlayerScore> leaderboard =
			{
				{game.inputText,  game.numEatenApples},
				{"Alice",  Alice},
				{"Bob",     Bob},
				{"Carol",   Carol},
				{"Dave",    Dave},
				{"Eve",     Eve}
			};
			if (event.type == sf::Event::Closed)
			{
				game.saveGame();
				window.close();
				break;
				delete[] game.apples;
			}
			//if (game.isGame == false)
			//{
			//	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			//	{
			//		window.close();
			//		break;
			//		delete[] game.apples;
			//	}
			//}
		}

		UpdateGame(game, deltaTime);

		if (game.numEatenApples > game.MaxNumEatenApples)
		{
			game.MaxNumEatenApples = game.numEatenApples;
		}

		// Draw game
		window.clear();
		DrawGame(game.back1, game, window);

		NadoMenu(game, window);
		NadoMenu_Start(game, window);
		NadoMenu_Difficulty_Level(game, window);
		NadoMenu_Settings(game, window);

		if (Menu_Leader_Board == true) // Menu_Leader_Board
		{
			sortLeaderboard(leaderboard);
			float y = 330;
			// Заголовок
			sf::Text title("===== LEADERBOARD =====", game.font, 24);
			title.setFillColor(sf::Color::Red);
			title.setPosition(250, y - 30);
			window.draw(title);

			const float lineHeight = 30.0f;
			const int maxLineLen = 28;

			for (size_t i = 0; i < leaderboard.size(); ++i) {
				std::string line = std::to_string(i + 1) + ". " + leaderboard[i].name;
				int dotsNeeded = maxLineLen - static_cast<int>(line.length());
				if (dotsNeeded < 1) dotsNeeded = 1;

				std::string dots(dotsNeeded, '.');
				std::string fullLine = line + dots + std::to_string(leaderboard[i].score);

				sf::Text text(fullLine, game.font, 20);
				text.setFillColor(sf::Color::Red);
				text.setPosition(250, y);
				window.draw(text);

				y += lineHeight;
			}

			sf::Text footer("=======================", game.font, 24);
			footer.setFillColor(sf::Color::Red);
			footer.setPosition(250, y + 10);
			window.draw(footer);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				Menu_Leader_Board = false;
				Menu_Start = true;
				game.pauseCooldownf.restart();             // сбрасываем таймер
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
				{
					game.selectedIndex--;
					if (game.selectedIndex < 0)game.selectedIndex = static_cast<int>(Leader_Board.size()) - 1;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
				{
					game.selectedIndex++;
					if (game.selectedIndex >= static_cast<int>(Leader_Board.size())) game.selectedIndex = 0;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				// Тут вызываем нужную логику в зависимости от выбора
				if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
				{
					if (game.selectedIndex == 1) {
						Menu_Start = true;
						Menu_Leader_Board = false;
						game.pauseCooldownf.restart();             // сбрасываем таймер
					}
				}
			}

			for (size_t i = 0; i < Leader_Board.size(); ++i) {
				sf::Text text(Leader_Board[i], game.font, 25);
				text.setFillColor(sf::Color(147, 112, 219));

				float y = game.startY + i * game.itemHeight;
				// Центрируем текст по горизонтали
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
				text.setPosition(window.getSize().x / 2.f, y);

				// Подсветка выбранного пункта
				if (static_cast<int>(i) == game.selectedIndex) {
					text.setFillColor(sf::Color(106, 90, 205));
					// Можно ещё добавить обводку или рамку, если хочется
				}

				window.draw(text);
			}
		}

		window.draw(scoreLabel);
		window.draw(scoreValue);
		window.draw(scoreLabel2);
		window.draw(scoreValue2);

		// TextR
		sf::Text TextR("A-left, W-forward, S-backward, D-right, P-menu, tab-leaderboard", game.font, 15);
		TextR.setFillColor(sf::Color::White);
		TextR.setPosition(310, -3.f);
		window.draw(TextR);
		if (game.name == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				if (game.pauseCooldown.getElapsedTime().asSeconds() >= game.pauseDelay)
				{
					game.isGamepause = (game.isGamepause ? false : true);
					game.pauseCooldown.restart();             // сбрасываем таймер
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			sf::RectangleShape Blackcube(sf::Vector2f(400.f, 300.f));
			Blackcube.setFillColor(sf::Color::Black);

			// Центрируем кубик в окне
			Blackcube.setPosition(SCREEN_WIDTH - 600.f, SCREEN_HEIGHT / 3.5f);

			// Отрисовка кубика
			window.draw(Blackcube);
			sortLeaderboard(leaderboard);
			float y = 230;
			// Заголовок
			sf::Text title("===== LEADERBOARD =====", game.font, 24);
			title.setFillColor(sf::Color::Red);
			title.setPosition(250, y - 30);
			window.draw(title);

			const float lineHeight = 30.0f;
			const int maxLineLen = 28;

			for (size_t i = 0; i < leaderboard.size(); ++i) {
				std::string line = std::to_string(i + 1) + ". " + leaderboard[i].name;
				int dotsNeeded = maxLineLen - static_cast<int>(line.length());
				if (dotsNeeded < 1) dotsNeeded = 1;

				std::string dots(dotsNeeded, '.');
				std::string fullLine = line + dots + std::to_string(leaderboard[i].score);

				sf::Text text(fullLine, game.font, 20);
				text.setFillColor(sf::Color::Red);
				text.setPosition(250, y);
				window.draw(text);

				y += lineHeight;
			}

			sf::Text footer("=======================", game.font, 24);
			footer.setFillColor(sf::Color::Red);
			footer.setPosition(250, y + 10);
			window.draw(footer);
		}

		if (game.isGameFinished == true)
		{
			if (game.nadoname == true)
			{
				sf::RectangleShape Blackcube(sf::Vector2f(450.f, 200.f));
				Blackcube.setFillColor(sf::Color::Black);

				// Центрируем кубик в окне
				Blackcube.setPosition(SCREEN_WIDTH - 623.f, SCREEN_HEIGHT - 440);

				// Отрисовка кубика
				window.draw(Blackcube);
				if (game.prename == true)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
						{
							game.selectedIndex--;
							if (game.selectedIndex < 0) game.selectedIndex = static_cast<int>(death.size()) - 1;
							game.pauseCooldownf.restart();             // сбрасываем таймер
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
						{
							game.selectedIndex++;
							if (game.selectedIndex >= static_cast<int>(death.size())) game.selectedIndex = 0;
							game.pauseCooldownf.restart();             // сбрасываем таймер
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
						{
							// Тут вызываем нужную логику в зависимости от выбора
							if (game.selectedIndex == 1) {
								// Reset backgound
								game.background.setFillColor(sf::Color::Black);
								RestartGame(game.back1, game);
								game.pauseCooldownf.restart();             // сбрасываем таймер
							}
							else if (game.selectedIndex == 2) {
								game.name = true;
								game.pauseCooldownf.restart();             // сбрасываем таймер
							}
						}
					}
					for (size_t i = 0; i < prenameM.size(); ++i) {
						sf::Text text(prenameM[i], game.font, 25);
						text.setFillColor(sf::Color(147, 112, 219));

						float y2 = 200 + i * game.itemHeight;
						// Центрируем текст по горизонтали
						sf::FloatRect textRect = text.getLocalBounds();
						text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
						text.setPosition(window.getSize().x / 2.f, y2);

						// Подсветка выбранного пункта
						if (static_cast<int>(i) == game.selectedIndex) {
							text.setFillColor(sf::Color(106, 90, 205));
							// Можно ещё добавить обводку или рамку, если хочется
						}

						window.draw(text);
					}
				}
				if (game.name == true)
				{
					game.prename = false;
					// Textx
					sf::Text TextX("Use keyboard to type", game.font, 25);
					TextX.setFillColor(sf::Color::Yellow);
					TextX.setPosition(SCREEN_WIDTH - 590, SCREEN_HEIGHT - 380); // слева сверху
					window.draw(TextX);

					if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
					{
						// Сюда попадает именно символ (удобнее, чем KeyPressed для ввода текста)
						if (event.type == sf::Event::TextEntered) {
							// Пропускаем спецсимволы, которые не хотим видеть
							if (event.text.unicode >= 32 && event.text.unicode < 127) {
								game.inputText += static_cast<char>(event.text.unicode);
							}
							// Backspace
							else if (event.text.unicode == 8) { // 8 — это backspace
								if (!game.inputText.empty())
									game.inputText.pop_back();
							}

							// Обновляем текст на экране
							game.INtext.setString(game.inputText);
							game.pauseCooldownf.restart();             // сбрасываем таймер
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							game.name = false;
							game.nadoname = false;
							game.pauseCooldownf.restart();             // сбрасываем таймер

						}
					}
					window.draw(game.INtext);
				}
			}

			if (game.nadoname == false)
			{
				sf::RectangleShape Blackcube(sf::Vector2f(550.f, 500.f));
				Blackcube.setFillColor(sf::Color::Black);

				// Центрируем кубик в окне
				Blackcube.setPosition(SCREEN_WIDTH - 675.f, SCREEN_HEIGHT - 540);

				// Отрисовка кубика
				window.draw(Blackcube);
				sortLeaderboard(leaderboard);
				float y3 = 330;
				// Заголовок
				sf::Text title("===== LEADERBOARD =====", game.font, 24);
				title.setFillColor(sf::Color::Red);
				title.setPosition(250, y3 - 30);
				window.draw(title);

				const float lineHeight = 30.0f;
				const int maxLineLen = 28;

				for (size_t i = 0; i < leaderboard.size(); ++i) {
					std::string line = std::to_string(i + 1) + ". " + leaderboard[i].name;
					int dotsNeeded = maxLineLen - static_cast<int>(line.length());
					if (dotsNeeded < 1) dotsNeeded = 1;

					std::string dots(dotsNeeded, '.');
					std::string fullLine = line + dots + std::to_string(leaderboard[i].score);

					sf::Text text(fullLine, game.font, 20);
					text.setFillColor(sf::Color::Red);
					text.setPosition(250, y3);
					window.draw(text);

					y3 += lineHeight;
				}

				sf::Text footer("=======================", game.font, 24);
				footer.setFillColor(sf::Color::Red);
				footer.setPosition(250, y3 + 10);
				window.draw(footer);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
				{

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
					{
						game.selectedIndex--;
						if (game.selectedIndex < 0) game.selectedIndex = static_cast<int>(death.size()) - 1;
						game.pauseCooldownf.restart();             // сбрасываем таймер
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					if (game.pauseCooldownf.getElapsedTime().asSeconds() >= game.pauseDelayf)
					{
						game.selectedIndex++;
						if (game.selectedIndex >= static_cast<int>(death.size())) game.selectedIndex = 0;
						game.pauseCooldownf.restart();             // сбрасываем таймер
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					// Тут вызываем нужную логику в зависимости от выбора
					if (game.selectedIndex == 1) {
						// Reset backgound
						game.background.setFillColor(sf::Color::Black);
						RestartGame(game.back1, game);
					}
					if (game.selectedIndex == 2) {
						game.isGame = false;
						game.isGamepause = false;
						// Reset backgound
						game.background.setFillColor(sf::Color::Black);
						RestartGame(game.back1, game);
						Menu_Start = true;
						Menu_Leader_Board = false;
						game.pauseCooldownf.restart();             // сбрасываем таймер
					}
					else if (game.selectedIndex == 3) {
						game.saveGame();
						window.close();
						break;
						delete[] game.apples;
					}
				}
				for (size_t i = 0; i < death.size(); ++i) {
					sf::Text text(death[i], game.font, 25);
					text.setFillColor(sf::Color(147, 112, 219));

					float y2 = 100 + i * game.itemHeight;
					// Центрируем текст по горизонтали
					sf::FloatRect textRect = text.getLocalBounds();
					text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
					text.setPosition(window.getSize().x / 2.f, y2);

					// Подсветка выбранного пункта
					if (static_cast<int>(i) == game.selectedIndex) {
						text.setFillColor(sf::Color(106, 90, 205));
						// Можно ещё добавить обводку или рамку, если хочется
					}

					window.draw(text);
				}


			}
		}

		window.display();
	}
	// Deinitialization
	DeinializeGame(game);

	return 0;
}
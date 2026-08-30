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

	// --- Шарик ---
	float ballRadius = 15.f;
	sf::Vector2f ballPos(SCREEN_WIDTH / 2.f, 100);
	float ballSpeedX = 0.2f;
	float ballSpeedY = 0.1f;

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

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				game.saveGame();
				window.close();
				break;
			}
		}
		game.platform.direction = PlatformDirection::Stop;
		UpdateGame(game, deltaTime);

		if (game.isGame == true)
		{
			if (game.isGamepause == false)
			{
				ballPos.x += ballSpeedX;
				ballPos.y += ballSpeedY;

				if (ballPos.x - ballRadius <= 0.f) {
					ballPos.x = ballRadius;
					ballSpeedX = -ballSpeedX;
				}
				else if (ballPos.x + ballRadius >= SCREEN_WIDTH) {
					ballPos.x = SCREEN_WIDTH - ballRadius;
					ballSpeedX = -ballSpeedX;
				}

				if (ballPos.y - ballRadius <= 0.f) {
					ballPos.y = ballRadius;
					ballSpeedY = -ballSpeedY;
				}
				else if (ballPos.y + ballRadius >= SCREEN_HEIGHT) {
					ballPos.y = SCREEN_HEIGHT - ballRadius;
					ballSpeedY = -ballSpeedY;
				}

				sf::FloatRect platformBounds = game.platform.PlatformOb.getGlobalBounds();

				float closestX = ballPos.x;
				float closestY = ballPos.y;

				if (closestX < platformBounds.left)
					closestX = platformBounds.left;
				else if (closestX > platformBounds.left + platformBounds.width)
					closestX = platformBounds.left + platformBounds.width;

				if (closestY < platformBounds.top)
					closestY = platformBounds.top;
				else if (closestY > platformBounds.top + platformBounds.height)
					closestY = platformBounds.top + platformBounds.height;

				float dx = ballPos.x - closestX;
				float dy = ballPos.y - closestY;
				float distSq = dx * dx + dy * dy;

				if (distSq < ballRadius * ballRadius) {
					float dist = std::sqrt(distSq);
					if (dist == 0.f) dist = 0.0001f;

					float nx = dx / dist;
					float ny = dy / dist;

					float overlap = ballRadius - dist;
					ballPos.x += nx * overlap;
					ballPos.y += ny * overlap;

					// V_new = V_old - 2 * (V_old · N) * N
					float dot = ballSpeedX * nx + ballSpeedY * ny;
					ballSpeedX -= 2.f * dot * nx;
					ballSpeedY -= 2.f * dot * ny;
				}
			}
		}

		// Draw game
		window.clear();
		DrawGame(game, window);

		// Рисуем шарик
		sf::CircleShape ball(ballRadius);
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(ballPos.x - ballRadius, ballPos.y - ballRadius);
		window.draw(ball);

		NadoMenu(game, window);
		NadoMenu_Start(game, window);
		NadoMenu_Difficulty_Level(game, window);
		NadoMenu_Settings(game, window);

		if (game.isGame == true)
		{
			if (game.isGamepause == false)
			{
				// TextR
				sf::Text TextR("<- left, -> right, P-menu", game.font, 15);
				TextR.setFillColor(sf::Color::White);
				TextR.setPosition(310, -3.f);
				window.draw(TextR);
			}
		}
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
								RestartGame(game);
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
				float y3 = 330;

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
					// Тут вызываем нужную логику в зависимости от выбора
					if (game.selectedIndex == 1) {
						// Reset backgound
						game.background.setFillColor(sf::Color::Black);
						RestartGame(game);
					}
					if (game.selectedIndex == 2) {
						game.isGame = false;
						game.isGamepause = false;
						// Reset backgound
						game.background.setFillColor(sf::Color::Black);
						RestartGame(game);
						Menu_Start = true;
						Menu_Leader_Board = false;
						game.pauseCooldownf.restart();             // сбрасываем таймер
					}
					else if (game.selectedIndex == 3) {
						game.saveGame();
						window.close();
						break;
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
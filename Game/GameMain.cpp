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
#include "Cube.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Game game;
	// 1. При старте — пытаемся загрузить
	loadGame(); 

	GameState state(10);
	//cube
	for (int i = 0; i < state.cubeCount; ++i) {
		InitCube(*state.cubes[i], game);
	}

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

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	InitCube(game.cube ,game);
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
				saveGame();
				window.close();
				break;
			}
		}
		game.platform.direction = PlatformDirection::Stop;

		if ((game.platform.position.x - 60.f) <= 0.f)
		{
			isTouchingLeft = true;
		}
		if ((game.platform.position.x + 60.f) >= 800.f)
		{
			isTouchingRight = true;
		}

		UpdateGame(game, deltaTime);

		if (isGame == true)
		{
			if (isGamepause == false)
			{
				if (deathfa == false)
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

						float dot = ballSpeedX * nx + ballSpeedY * ny;
						ballSpeedX -= 2.f * dot * nx;
						ballSpeedY -= 2.f * dot * ny;
					}

					// === ОТСКОК ОТ КУБОВ + УДАЛЕНИЕ + СЧЁТ ===
					for (int i = 0; i < state.cubeCount; ++i) {
						if (!state.cubes[i]->active)
							continue;

						sf::FloatRect cubeBounds = state.cubes[i]->CubeOb.getGlobalBounds();

						closestX = ballPos.x;
						closestY = ballPos.y;

						if (closestX < cubeBounds.left)
							closestX = cubeBounds.left;
						else if (closestX > cubeBounds.left + cubeBounds.width)
							closestX = cubeBounds.left + cubeBounds.width;

						if (closestY < cubeBounds.top)
							closestY = cubeBounds.top;
						else if (closestY > cubeBounds.top + cubeBounds.height)
							closestY = cubeBounds.top + cubeBounds.height;

						dx = ballPos.x - closestX;
						dy = ballPos.y - closestY;
						distSq = dx * dx + dy * dy;

						if (distSq < ballRadius * ballRadius) {
							float dist = std::sqrt(distSq);
							if (dist == 0.f) dist = 0.0001f;

							float nx = dx / dist;
							float ny = dy / dist;

							float overlap = ballRadius - dist;
							ballPos.x += nx * overlap;
							ballPos.y += ny * overlap;

							float dot = ballSpeedX * nx + ballSpeedY * ny;
							ballSpeedX -= 2.f * dot * nx;
							ballSpeedY -= 2.f * dot * ny;

							state.cubes[i]->active = false;
							score++;
						}
					}

				}
			}
		}

		// Draw game
		window.clear();
		DrawGame(game, window);

		//cube
		for (int i = 0; i < state.cubeCount; ++i) {
			DrawCube(*state.cubes[i], window);
		}

		// Рисуем шарик
		sf::CircleShape ball(ballRadius);
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(ballPos.x - ballRadius, ballPos.y - ballRadius);
		window.draw(ball);

		NadoMenu(game, window);
		NadoMenu_Start(game, window);
		NadoMenu_Difficulty_Level(game, window);
		NadoMenu_Settings(game, window);

		if (deathfa == true) // Menu_Settings
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				Menu_Settings = false;
				Menu_Start = true;
				game.pauseCooldownf.restart();             // сбрасываем таймер
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
				{
					selectedIndex--;
					if (selectedIndex < 0) selectedIndex = static_cast<int>(Difficulty_Level.size()) - 1;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
				{
					selectedIndex++;
					if (selectedIndex >= static_cast<int>(Difficulty_Level.size())) selectedIndex = 0;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				// Тут вызываем нужную логику в зависимости от выбора
				if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
				{
					if (selectedIndex == 1) {
						for (int i = 0; i < state.cubeCount; ++i) {
							if (state.cubes[i] != nullptr) {
								delete state.cubes[i];
								state.cubes[i] = nullptr; 
							}
						}
						ballPos.x = SCREEN_WIDTH / 2.f;
						ballPos.y = 100.f;
						ballSpeedX = 0.2f;
						ballSpeedY = 0.1f;
						game.platform.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f };
						state.cubeCount = 10;
						for (int i = 0; i < state.cubeCount; ++i) {
							state.cubes[i] = new Cube();
						}
						for (int i = 0; i < state.cubeCount; ++i) {
							InitCube(*state.cubes[i], game);
						}
						game.pauseCooldownf.restart();
						score = 0;
						deathfa = false;
					}
					else if (selectedIndex == 2) {
						saveGame();
						window.close();
					}
					if (selectedIndex == 2) {
						saveGame();
						window.close();
					}
				}
			}
			for (size_t i = 0; i < death.size(); ++i) {
				sf::Text text(death[i], game.font, 25);
				text.setFillColor(sf::Color(147, 112, 219));

				float y = startY + i * itemHeight;
				// Центрируем текст по горизонтали
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
				text.setPosition(window.getSize().x / 2.f, y);

				// Подсветка выбранного пункта
				if (static_cast<int>(i) == selectedIndex) {
					text.setFillColor(sf::Color(106, 90, 205));
					// Можно ещё добавить обводку или рамку, если хочется.
				}

				window.draw(text);
			}
		}

		if (isGame == true)
		{
			if (isGamepause == false)
			{
				// TextR
				sf::Text TextR("<- left, -> right, P-menu", game.font, 15);
				TextR.setFillColor(sf::Color::White);
				TextR.setPosition(310, -3.f);
				window.draw(TextR);
			}
		}
		if (score >= 10 )
		{
			deathfa = true;
		}
		window.display();
	}
	// Deinitialization
	DeinializeGame(game);

	return 0;
}
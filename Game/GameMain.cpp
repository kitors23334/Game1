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
#include "physics.h"

int main()
{
	sf::Clock clock;
	srand(static_cast<unsigned int>(time(nullptr)));
	Game game;

	GameState state(5, 5);
	//cube
	for (int i = 0; i < state.cubeCount; ++i) {
		InitCube(*state.cubes[i], game);
	}
	//simplecube
	for (int i = 0; i < state.simplecubeCount; ++i) {
		InitSimpleCube(*state.simplecubes[i], game);
	}

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	InitCube(game.cube ,game);
	InitSimpleCube(game.simplecube, game);
	InitBall(game.ball, game);
	InitGame(state, game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
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

		float dt = clock.restart().asSeconds();

		if (isGameFinished == false)
		{
			if (isGameStarted == true)
			{
				game.ball.position += game.ball.velocity * dt;
				UpdateBallWithWalls(game.ball, dt);
				if (CheckBallPlatformCollision(game.ball, game.platform)) {
					HandleBallPlatformBounce(game.ball, game.platform);
				}
				//1
				for (int i = 0; i < state.cubeCount; ++i) {
					Cube& cube = *state.cubes[i];
					if (!cube.isActive) continue;

					if (HandleBallCubeBounce(game.ball, cube)) {
						cube.isActive = false;  // куб исчезает
					}
				}
				//2
				for (int i = 0; i < state.simplecubeCount; ++i) {
					SimpleCube& simplecube = *state.simplecubes[i];
					if (!simplecube.isActive) continue;

					if (HandleBallSimpleCubeBounce(game.ball, simplecube)) {
						simplecube.isActive = false;  // куб исчезает
					}
				}
			}
		}
		UpdateGame(game, deltaTime);

		// Draw game
		window.clear();
		DrawGame(game, window);

		// draw cube
		for (int i = 0; i < state.cubeCount; ++i) {
			Cube& cube = *state.cubes[i];
			if (!cube.isActive) {
				continue;  // не рисуем
			}
			DrawCube(cube, window);
		}
		// draw simplecube
		for (int i = 0; i < state.simplecubeCount; ++i) {
			SimpleCube& simplecube = *state.simplecubes[i];
			if (!simplecube.isActive) {
				continue;  // не рисуем
			}
			DrawSimpleCube(simplecube, window);
		}
		NadoMenu_Start(game, window);
		NadoMenu_Restart(state, game, window);

		if (isGameStarted == true)
		{
			// TextR
			sf::Text TextR("<-/-> = left/right", game.font, 15);
			TextR.setFillColor(sf::Color::White);
			TextR.setPosition(310, -3.f);
			window.draw(TextR);
		}
		//0
		int inactiveCount = 0;
		//1
		for (int i = 0; i < state.cubeCount; ++i) {
			if (!state.cubes[i]->isActive) {
				inactiveCount++;
			}
		}
		//2
		for (int i = 0; i < state.simplecubeCount; ++i) {
			if (!state.simplecubes[i]->isActive) {
				inactiveCount++;
			}
		}
		// 3
		int totalCubes = state.cubeCount + state.simplecubeCount;
		if (inactiveCount == totalCubes) {
			Menu_Restart = true;  // Вот оно — срабатывает, когда все кубы обоих типов неактивны
		}
		window.display();
	}
	// Deinitialization
	DeinializeGame(game);

	return 0;
}
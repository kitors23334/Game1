#include "Menu.h"

void NadoMenu_Start(Game& game, sf::RenderWindow& window)
{
	if (Menu_Start == true) // старт меню
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
			{
				selectedIndex--;
				if (selectedIndex < 0) selectedIndex = static_cast<int>(Menu.size()) - 1;
				game.pauseCooldownf.restart();             // сбрасываем таймер
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
			{
				selectedIndex++;
				if (selectedIndex >= static_cast<int>(Menu.size())) selectedIndex = 0;
				game.pauseCooldownf.restart();             // сбрасываем таймер
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			// Тут вызываем нужную логику в зависимости от выбора
			if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
			{
				if (selectedIndex == 1) {
					game.PlayerpauseDelayf == 0.5f;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGameStarted = true;
					Menu_Start = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				else if (selectedIndex == 2) {
					window.close();
				}
			}
		}
		for (size_t i = 0; i < Menu.size(); ++i) {
			sf::Text text(Menu[i], game.font, 25);
			text.setFillColor(sf::Color(147, 112, 219));

			float y = startY + i * itemHeight;
			// Центрируем текст по горизонтали
			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
			text.setPosition(window.getSize().x / 2.f, y);

			// Подсветка выбранного пункта
			if (static_cast<int>(i) == selectedIndex) {
				text.setFillColor(sf::Color(106, 90, 205));
				// Можно ещё добавить обводку или рамку, если хочется
			}

			window.draw(text);
		}
	}
}

// RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART RESTART

void NadoMenu_Restart(GameState& state, Game& game, sf::RenderWindow& window)
{
	if (Menu_Restart == true) // старт меню
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
			{
				selectedIndex--;
				if (selectedIndex < 0) selectedIndex = static_cast<int>(MenuRestart.size()) - 1;
				game.pauseCooldownf.restart();             // сбрасываем таймер
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
			{
				selectedIndex++;
				if (selectedIndex >= static_cast<int>(MenuRestart.size())) selectedIndex = 0;
				game.pauseCooldownf.restart();             // сбрасываем таймер
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			// Тут вызываем нужную логику в зависимости от выбора
			if (game.pauseCooldownf.getElapsedTime().asSeconds() >= pauseDelayf)
			{
				if (selectedIndex == 1) {
					game.PlayerpauseDelayf == 0.5f;
					isGameFinished = false;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					score = 0;
					isGameStarted = true;
					Menu_Restart = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
					//reset ball
					game.ball.position = { SCREEN_WIDTH / 2.f, 100 };
					//reset cube
					for (int i = 0; i < state.cubeCount; ++i) {
						Cube& c = *state.cubes[i];
						InitCube(*state.cubes[i], game);
						c.maxBounces = rand() % 2 + 2;
						c.isActive = true;
						c.bounceCount = 0;
						c.UpdateColor();
					}
					//reset simplecube
					for (int i = 0; i < state.simplecubeCount; ++i) {
						SimpleCube& sc = *state.simplecubes[i];
						InitSimpleCube(*state.simplecubes[i], game);
						sc.isActive = true;
						sc.bounceCount = 0;
					}
					InitCube(game.cube, game);
					InitSimpleCube(game.simplecube, game);
				}
				else if (selectedIndex == 2) {
					window.close();
				}
			}
		}
		for (size_t i = 0; i < MenuRestart.size(); ++i) {
			sf::Text text(MenuRestart[i], game.font, 25);
			text.setFillColor(sf::Color(147, 112, 219));

			float y = startY + i * itemHeight;
			// Центрируем текст по горизонтали
			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
			text.setPosition(window.getSize().x / 2.f, y);

			// Подсветка выбранного пункта
			if (static_cast<int>(i) == selectedIndex) {
				text.setFillColor(sf::Color(106, 90, 205));
				// Можно ещё добавить обводку или рамку, если хочется
			}

			window.draw(text);
		}
	}
}
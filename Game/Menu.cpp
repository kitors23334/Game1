#include "Menu.h"

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
void NadoMenu(Game& game, sf::RenderWindow& window)
{
	if (isGamepause == true)
	{
		sf::RectangleShape Blackcube(sf::Vector2f(550.f, 300.f));
		Blackcube.setFillColor(sf::Color::Black);

		// Центрируем кубик в окне
		Blackcube.setPosition(SCREEN_WIDTH - 680.f, SCREEN_HEIGHT / 3.5f);

		// Отрисовка кубика
		window.draw(Blackcube);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{

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
					// Продолжить игру: просто выходим из меню
					isGamepause = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 2) {
					isGame = false;
					isGamepause = false;
					Menu_Start = true;
					Menu_Leader_Board = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				else if (selectedIndex == 3) {
					saveGame();
					window.close();
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
		}
		for (size_t i = 0; i < options.size(); ++i) {
			sf::Text text(options[i], game.font, 25);
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

void NadoMenu_Start(Game& game, sf::RenderWindow& window)
{
	if (Menu_Start == true) // старт меню
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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
					NUM_APPLES = 10;
					game.PlayerpauseDelayf == 0.5f;
					isGameFinished = true;
					isGame = true;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGame = true;
					Menu_Start = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 2) {
					Menu_Settings = true;
					Menu_Start = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				else if (selectedIndex == 3) {
					saveGame();
					window.close();
				}
			}
		}
		for (size_t i = 0; i < menu.size(); ++i) {
			sf::Text text(menu[i], game.font, 25);
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
void NadoMenu_Difficulty_Level(Game& game, sf::RenderWindow& window)
{
	if (Menu_Difficulty_Level == true) // Menu_Difficulty_Level
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			Menu_Difficulty_Level = false;
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
					NUM_APPLES = 10;
					game.PlayerpauseDelayf == 0.5f;
					isGameFinished = true;
					isGame = true;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGame = true;
					Menu_Difficulty_Level = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 2) {
					NUM_APPLES = 20;
					game.PlayerpauseDelayf == 0.4f;
					isGameFinished = true;
					isGame = true;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGame = true;
					Menu_Difficulty_Level = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 3) {
					NUM_APPLES = 20;
					game.PlayerpauseDelayf == 0.3f;
					isGameFinished = true;
					isGame = true;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGame = true;
					Menu_Difficulty_Level = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 4) {
					NUM_APPLES = 50;
					game.PlayerpauseDelayf == 0.2f;
					isGameFinished = true;
					isGame = true;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGame = true;
					Menu_Difficulty_Level = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 5) {
					NUM_APPLES = 50;
					game.PlayerpauseDelayf == 0.1f;
					isGameFinished = true;
					isGame = true;
					timeSinceGameFinish = 0.f;
					RestartGame(game);
					isGame = true;
					Menu_Difficulty_Level = false;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 6) {
					Menu_Difficulty_Level = false;
					Menu_Start = true;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
		}
		for (size_t i = 0; i < Difficulty_Level.size(); ++i) {
			sf::Text text(Difficulty_Level[i], game.font, 25);
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

void NadoMenu_Settings(Game& game, sf::RenderWindow& window)
{
	if (Menu_Settings == true) // Menu_Settings
	{
		const std::vector<std::string> Settings = {
		"Enter = choose, W = up, S = down, B = Return",
		music_stext,
		sounds_stext,
		"back"
		};
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
					music = (music ? false : true);
					if (music == true) {
						music_stext = "music<=";
					}
					if (music == false) {
						music_stext = "music";
					}
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 2) {
					sounds = (sounds ? false : true);
					if (sounds == true) {
						sounds_stext = "sounds<=";
					}
					if (sounds == false) {
						sounds_stext = "sounds";
					}
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
				if (selectedIndex == 3) {
					Menu_Settings = false;
					Menu_Start = true;
					game.pauseCooldownf.restart();             // сбрасываем таймер
				}
			}
		}
		for (size_t i = 0; i < Settings.size(); ++i) {
			sf::Text text(Settings[i], game.font, 25);
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
}

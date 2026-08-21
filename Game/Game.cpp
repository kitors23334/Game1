#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void RestartGame(Back1& back1, Game& game)
{
	game.StopSpawn = 0;
	game.AppleEatSound.setBuffer(game.AppleEatbuffer);
	game.DeathSound.setBuffer(game.DeathSoundbuffer);

	game.AppleEatSound.setVolume(Volume);
	game.DeathSound.setVolume(Volume);


	InitPlayer(game.player, game);

	// Back
	back1.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
	back1.BackSprite.setTexture(game.BackTexture);
	setSpriteSize(back1.BackSprite, 800, 600);
	setSpriteOrigin(back1.BackSprite, 0.5f, 0.5f);

	// Init apples
	for (int i = 0; i < NUM_APPLES; ++i)
	{
		InitApple(game.apples[i], game);
	}

	game.numEatenApples = 0;
	game.isGameFinished = false;
	game.timeSinceGameFinish = 0;
}

void InitGame(Game& game)
{
	int seed = (int)time(nullptr);
	srand(seed);

	assert(game.BackTexture.loadFromFile(RESOURCES_PATH + "\\back.png"));
	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
	assert(game.AppleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));

	assert(game.HeadUp.loadFromFile(RESOURCES_PATH + "\\snake_Up.png"));
	assert(game.HeadDown.loadFromFile(RESOURCES_PATH + "\\snake_Down.png"));
	assert(game.HeadLeft.loadFromFile(RESOURCES_PATH + "\\snake_Left.png"));
	assert(game.HeadRight.loadFromFile(RESOURCES_PATH + "\\snake_Rigth.png"));

	assert(game.BodyLR.loadFromFile(RESOURCES_PATH + "\\snake_Left-Rigth.png"));
	assert(game.BodyUD.loadFromFile(RESOURCES_PATH + "\\snake_Down-Up.png"));

	assert(game.TurnLU.loadFromFile(RESOURCES_PATH + "\\snake_Left-Up.png"));
	assert(game.TurnLD.loadFromFile(RESOURCES_PATH + "\\snake_Left-Down.png"));
	assert(game.TurnRU.loadFromFile(RESOURCES_PATH + "\\snake_Rigth-Up.png"));
	assert(game.TurnDR.loadFromFile(RESOURCES_PATH + "\\snake_Down-Rigth.png"));

	assert(game.TailUp.loadFromFile(RESOURCES_PATH + "\\snake_Up_fin.png"));
	assert(game.TailDown.loadFromFile(RESOURCES_PATH + "\\snake_Down_fin.png"));
	assert(game.TailLeft.loadFromFile(RESOURCES_PATH + "\\snake_Left_fin.png"));
	assert(game.TailRight.loadFromFile(RESOURCES_PATH + "\\snake_Rigth_fin.png"));

	// Головы
	game.HeadUpSprite.setTexture(game.HeadUp);
	game.HeadUpSprite.setOrigin(game.HeadUpSprite.getLocalBounds().width / 2.f, game.HeadUpSprite.getLocalBounds().height / 2.f);
	game.HeadUpSprite.setScale(game.segmentSize, game.segmentSize);

	game.HeadDownSprite.setTexture(game.HeadDown);
	game.HeadDownSprite.setOrigin(game.HeadDownSprite.getLocalBounds().width / 2.f, game.HeadDownSprite.getLocalBounds().height / 2.f);
	game.HeadDownSprite.setScale(game.segmentSize, game.segmentSize);

	game.HeadLeftSprite.setTexture(game.HeadLeft);
	game.HeadLeftSprite.setOrigin(game.HeadLeftSprite.getLocalBounds().width / 2.f, game.HeadLeftSprite.getLocalBounds().height / 2.f);
	game.HeadLeftSprite.setScale(game.segmentSize, game.segmentSize);

	game.HeadRightSprite.setTexture(game.HeadRight);
	game.HeadRightSprite.setOrigin(game.HeadRightSprite.getLocalBounds().width / 2.f, game.HeadRightSprite.getLocalBounds().height / 2.f);
	game.HeadRightSprite.setScale(game.segmentSize, game.segmentSize);

	// Тело
	game.BodyLRSprite.setTexture(game.BodyLR);
	game.BodyLRSprite.setOrigin(game.BodyLRSprite.getLocalBounds().width / 2.f, game.BodyLRSprite.getLocalBounds().height / 2.f);
	game.BodyLRSprite.setScale(game.segmentSize, game.segmentSize);

	game.BodyUDSprite.setTexture(game.BodyUD);
	game.BodyUDSprite.setOrigin(game.BodyUDSprite.getLocalBounds().width / 2.f, game.BodyUDSprite.getLocalBounds().height / 2.f);
	game.BodyUDSprite.setScale(game.segmentSize, game.segmentSize);

	// Повороты
	game.TurnLUSprite.setTexture(game.TurnLU);
	game.TurnLUSprite.setOrigin(game.TurnLUSprite.getLocalBounds().width / 2.f, game.TurnLUSprite.getLocalBounds().height / 2.f);
	game.TurnLUSprite.setScale(game.segmentSize, game.segmentSize);

	game.TurnLDSprite.setTexture(game.TurnLD);
	game.TurnLDSprite.setOrigin(game.TurnLDSprite.getLocalBounds().width / 2.f, game.TurnLDSprite.getLocalBounds().height / 2.f);
	game.TurnLDSprite.setScale(game.segmentSize, game.segmentSize);

	game.TurnRUSprite.setTexture(game.TurnRU);
	game.TurnRUSprite.setOrigin(game.TurnRUSprite.getLocalBounds().width / 2.f, game.TurnRUSprite.getLocalBounds().height / 2.f);
	game.TurnRUSprite.setScale(game.segmentSize, game.segmentSize);

	game.TurnDRSprite.setTexture(game.TurnDR);
	game.TurnDRSprite.setOrigin(game.TurnDRSprite.getLocalBounds().width / 2.f, game.TurnDRSprite.getLocalBounds().height / 2.f);
	game.TurnDRSprite.setScale(game.segmentSize, game.segmentSize);

	// Хвосты
	game.TailUpSprite.setTexture(game.TailUp);
	game.TailUpSprite.setOrigin(game.TailUpSprite.getLocalBounds().width / 2.f, game.TailUpSprite.getLocalBounds().height / 2.f);
	game.TailUpSprite.setScale(game.segmentSize, game.segmentSize);

	game.TailDownSprite.setTexture(game.TailDown);
	game.TailDownSprite.setOrigin(game.TailDownSprite.getLocalBounds().width / 2.f, game.TailDownSprite.getLocalBounds().height / 2.f);
	game.TailDownSprite.setScale(game.segmentSize, game.segmentSize);

	game.TailLeftSprite.setTexture(game.TailLeft);
	game.TailLeftSprite.setOrigin(game.TailLeftSprite.getLocalBounds().width / 2.f, game.TailLeftSprite.getLocalBounds().height / 2.f);
	game.TailLeftSprite.setScale(game.segmentSize, game.segmentSize);

	game.TailRightSprite.setTexture(game.TailRight);
	game.TailRightSprite.setOrigin(game.TailRightSprite.getLocalBounds().width / 2.f, game.TailRightSprite.getLocalBounds().height / 2.f);
	game.TailRightSprite.setScale(game.segmentSize, game.segmentSize);


	assert(game.AppleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));

	if (!game.AppleEatbuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav")) {
	}
	if (!game.DeathSoundbuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav")) {
	}
	if (game.font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
	}
	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.f, 0.f);

	RestartGame(game.back1, game);
}

void UpdateGame(Game& game, float deltaTime)
{
	Player player;
	if (game.isGame == true)
	{
		// Update game state
		if (!game.isGameFinished)
		{
			if (game.isGamepause == false)
			{
				// Handle input
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					game.player.direction = PlayerDirection::Right;
					playerRight(game.player);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					game.player.direction = PlayerDirection::Up;
					playerUp(game.player);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					game.player.direction = PlayerDirection::Left;
					playerLeft(game.player);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					game.player.direction = PlayerDirection::Down;
					playerDown(game.player);
				}
				// Update player state
				switch (game.player.direction)
				{
				case PlayerDirection::Right:
				{
					if (game.PlayerCooldownf.getElapsedTime().asSeconds() >= game.PlayerpauseDelayf)
					{
						TailSegment newHead;
						newHead.pos.x = game.player.position.x;
						newHead.pos.y = game.player.position.y;
						newHead.dir = game.player.direction;

						game.tailSegments.insert(game.tailSegments.begin(), newHead);

						if (game.tailSegments.size() > static_cast<size_t>(game.maxTailLength)) {
							game.tailSegments.pop_back();
						}
						//steps += 1;
						game.player.position.x += Size_Kletko;
						game.PlayerCooldownf.restart();             // сбрасываем таймер
						break;
					}
				}
				case PlayerDirection::Up:
				{
					if (game.PlayerCooldownf.getElapsedTime().asSeconds() >= game.PlayerpauseDelayf)
					{
						TailSegment newHead;
						newHead.pos.x = game.player.position.x;
						newHead.pos.y = game.player.position.y;
						newHead.dir = game.player.direction;

						game.tailSegments.insert(game.tailSegments.begin(), newHead);

						if (game.tailSegments.size() > static_cast<size_t>(game.maxTailLength)) {
							game.tailSegments.pop_back();
						}
						//steps += 1;
						game.player.position.y -= Size_Kletko;
						game.PlayerCooldownf.restart();             // сбрасываем таймер
						break;
					}
				}
				case PlayerDirection::Left:
				{
					if (game.PlayerCooldownf.getElapsedTime().asSeconds() >= game.PlayerpauseDelayf)
					{
						TailSegment newHead;
						newHead.pos.x = game.player.position.x;
						newHead.pos.y = game.player.position.y;
						newHead.dir = game.player.direction;

						game.tailSegments.insert(game.tailSegments.begin(), newHead);

						if (game.tailSegments.size() > static_cast<size_t>(game.maxTailLength)) {
							game.tailSegments.pop_back();
						}
						//steps += 1;
						game.player.position.x -= Size_Kletko;
						game.PlayerCooldownf.restart();             // сбрасываем таймер;
						break;
					}
				}
				case PlayerDirection::Down:
				{
					if (game.PlayerCooldownf.getElapsedTime().asSeconds() >= game.PlayerpauseDelayf)
					{
						TailSegment newHead;
						newHead.pos.x = game.player.position.x;
						newHead.pos.y = game.player.position.y;
						newHead.dir = game.player.direction;

						game.tailSegments.insert(game.tailSegments.begin(), newHead);

						if (game.tailSegments.size() > static_cast<size_t>(game.maxTailLength)) {
							game.tailSegments.pop_back();
						}

						//steps += 1;
						game.player.position.y += Size_Kletko;
						game.PlayerCooldownf.restart();             // сбрасываем таймер
						break;
					}
				}
				}
			}


			// Проходим по всем сегментам хвоста, которые сейчас видны
			for (int i = 0; i < game.maxTailLength; ++i) {
				// Защита от выхода за границы истории (на случай рассинхронизации)
				if (i >= static_cast<int>(game.tailSegments.size())) {
					break;
				}

				const auto& tailPos = game.tailSegments[i].pos;

				// Сравниваем координаты игрока и сегмента хвоста
				// Используем точное сравнение, так как позиции кратны размеру клетки (Size_Kletko)
				if (game.player.position.x == tailPos.x && game.player.position.y == tailPos.y) {
					game.isGameFinished = true;
					game.maxTailLength = 0;
					game.tailSegments.clear();
					game.timeSinceGameFinish = 0.f;
					if (sounds == true)
					{
						game.DeathSound.play();
					}
				}
			}

			// Find player collisions with apples
			for (int i = 0; i < NUM_APPLES; ++i)
			{
				if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
					game.apples[i].position, APPLE_SIZE / 2.f))
				{
					game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					++game.numEatenApples;
					game.maxTailLength += 1;
					//game.Bsnake = true;
					if (sounds == true)
					{
						game.AppleEatSound.play();
					}
				}
				if (game.StopSpawn == true)
				{
					if (game.numEatenApples == 50)
					{
						game.isGameFinished = true;
						game.timeSinceGameFinish = 0.f;
						if (sounds == true)
						{
							game.DeathSound.play();
						}
					}
				}
			}

			// Check screen borders collision
			if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				game.maxTailLength = 0;
				game.tailSegments.clear();
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;
				if (sounds == true)
				{
					game.DeathSound.play();
				}
			}
		}
		else //при смерти
		{
				game.timeSinceGameFinish += deltaTime;
				game.background.setFillColor(sf::Color::Red);
		}
	}
}

void DrawGame(Back1& back1, Game& game, sf::RenderWindow& window)
{
	window.draw(game.background);
	if (game.isGame == true)
	{
		back1.BackSprite.setPosition(back1.position.x, back1.position.y);
		window.draw(back1.BackSprite);
	}
	DrawPlayer(game.player, window);
	sf::CircleShape ball(Size_Kletko / 2.f);
	ball.setFillColor(sf::Color(255, 222, 90));
	ball.setOrigin(Size_Kletko / 2.f, Size_Kletko / 2.f);

	if (game.isGame == true)
	{
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			DrawApple(game.apples[i], window);
		}
	}
	sf::RectangleShape segment;
	segment.setSize(sf::Vector2f(Size_Kletko, Size_Kletko));
	segment.setOrigin(Size_Kletko / 2.f, Size_Kletko / 2.f); // центр вращения — центр клетки
	segment.setFillColor(sf::Color::Green);                 // цвет змейки

	// 1. Рисуем Голову
	sf::Sprite* headSprite = nullptr;
	switch (game.player.direction) {
	case PlayerDirection::Up:    headSprite = &game.HeadUpSprite;    break;
	case PlayerDirection::Down:  headSprite = &game.HeadDownSprite;  break;
	case PlayerDirection::Left:  headSprite = &game.HeadLeftSprite;  break;
	case PlayerDirection::Right: headSprite = &game.HeadRightSprite; break;
	default:                     headSprite = &game.HeadUpSprite;    break;
	}

	if (headSprite) {
		headSprite->setPosition(game.player.position.x, game.player.position.y);
		window.draw(*headSprite);
	}

	// 2. Рисуем Тело и Хвост
	for (size_t i = 0; i < game.tailSegments.size(); ++i) {
		const auto& seg = game.tailSegments[i];
		sf::Sprite* currentSprite = nullptr;

		// --- ИСПРАВЛЕНИЕ ХВОСТА ---
		// Хвост всегда смотрит в ту сторону, куда двигался этот сегмент
		if (i == game.tailSegments.size() - 1) {
			switch (seg.dir) {
			case PlayerDirection::Up:    currentSprite = &game.TailDownSprite;     break;
			case PlayerDirection::Down:  currentSprite = &game.TailUpSprite;   break;
			case PlayerDirection::Left:  currentSprite = &game.TailRightSprite;   break;
			case PlayerDirection::Right: currentSprite = &game.TailLeftSprite;  break;
			default:                     currentSprite = &game.TailUpSprite;     break;
			}
		}
		// --- ИСПРАВЛЕНИЕ ТЕЛА И ПОВОРОТОВ ---
		else {
			PlayerDirection nextDir = game.tailSegments[i + 1].dir;

			if (seg.dir == nextDir) {
				// Прямой участок
				if (seg.dir == PlayerDirection::Left || seg.dir == PlayerDirection::Right)
					currentSprite = &game.BodyLRSprite;
				else
					currentSprite = &game.BodyUDSprite;
			}
			else {
				// ПОВОРОТ: Полная таблица всех 8 вариантов
				// Примечание: Визуально спрайт Left->Up тот же самый, что и Down->Right.
				// Мы используем те 4 спрайта поворотов, которые у тебя уже есть.

				if (seg.dir == PlayerDirection::Left && nextDir == PlayerDirection::Up) // с низу на лево
					currentSprite = &game.TurnLDSprite;
				else if (seg.dir == PlayerDirection::Left && nextDir == PlayerDirection::Down) // с права на верх
					currentSprite = &game.TurnLUSprite;
				else if (seg.dir == PlayerDirection::Right && nextDir == PlayerDirection::Up)
					currentSprite = &game.TurnDRSprite;
				else if (seg.dir == PlayerDirection::Right && nextDir == PlayerDirection::Down) // с верху на право
					currentSprite = &game.TurnRUSprite;

				// Обратные повороты (из вертикального в горизонтальный)
				else if (seg.dir == PlayerDirection::Up && nextDir == PlayerDirection::Left) // с права на верх
					currentSprite = &game.TurnRUSprite;
				else if (seg.dir == PlayerDirection::Up && nextDir == PlayerDirection::Right) // с лево на верх
					currentSprite = &game.TurnLUSprite;
				else if (seg.dir == PlayerDirection::Down && nextDir == PlayerDirection::Left) // с права в низ
					currentSprite = &game.TurnDRSprite;
				else if (seg.dir == PlayerDirection::Down && nextDir == PlayerDirection::Right) // с лева в низ
					currentSprite = &game.TurnLDSprite;
			}
		}

		// Отрисовка
		if (currentSprite) {
			currentSprite->setPosition(seg.pos.x, seg.pos.y);
			window.draw(*currentSprite);
		}
	}


}

void DeinializeGame(Game& game)
{

}
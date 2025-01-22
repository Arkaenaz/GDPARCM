#include "pch.h"
#include "BaseRunner.h"

#include "GameObjectManager.h"
#include "TextureManager.h"

#include "BackgroundObject.h"
#include "FPSCounter.h"
#include "TextureDisplay.h"

const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE_LIMIT);
const float BaseRunner::GAME_SPEED = 1.0f;

BaseRunner::BaseRunner() :
	window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Threading Workbench", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar)
{
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	ShowWindow(window.getNativeHandle(), SW_MAXIMIZE);

	BackgroundObject* bgObject = new BackgroundObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	TextureDisplay* textureDisplay = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(textureDisplay);
}

void BaseRunner::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		processEvents();
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			update(elapsedTime * GAME_SPEED);
		}
		render();
	}
}

void BaseRunner::processEvents()
{
	while (const Event event = this->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->window.close();
		else
			GameObjectManager::getInstance()->processInput(event);
	}
}

void BaseRunner::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render()
{
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}
#include "pch.h"
#include "BaseRunner.h"

#include "GameObject/GameObjectManager.h"
#include "GameObject/TextureManager.h"

#include "GameObject/BackgroundObject.h"
#include "GameObject/FPSCounter.h"
#include "GameObject/TextureDisplay.h"

namespace IET {
	const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE_LIMIT);
	const float BaseRunner::GAME_SPEED = 1.0f;

	BaseRunner::BaseRunner() :
		window(sf::VideoMode(
			{ WINDOW_WIDTH, WINDOW_HEIGHT }),
			"[CABLAYAN] 08 - Interactive Loading Screen", 
			sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar)
	{
		Debug::Log(this, "Creating BaseRunner...");
		Debug::Log(this, "Setting Frame Rate Limit : " + std::to_string(FRAME_RATE_LIMIT));
		window.setFramerateLimit(FRAME_RATE_LIMIT);
		ShowWindow(window.getNativeHandle(), SW_MAXIMIZE);

		//load initial textures
		TextureManager::getInstance()->loadFromAssetList();

		FPSCounter* fpsCounter = new FPSCounter();
		GameObjectManager::getInstance()->addObject(fpsCounter);

		/*BackgroundObject* bgObject = new BackgroundObject("BGObject");
		GameObjectManager::getInstance()->addObject(bgObject);*/

		TextureDisplay* textureDisplay = new TextureDisplay();
		GameObjectManager::getInstance()->addObject(textureDisplay);
	}

	void BaseRunner::run()
	{
		const sf::Clock clock = sf::Clock::Clock();
		sf::Time previousDeltaTime = sf::Time::Zero;

		while (this->window.isOpen())
		{
			const sf::Time currentDeltaTime = clock.getElapsedTime();
			const sf::Time deltaTime = currentDeltaTime - previousDeltaTime;

			processEvents();
			update(deltaTime);
			render();

			previousDeltaTime = currentDeltaTime;
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
}

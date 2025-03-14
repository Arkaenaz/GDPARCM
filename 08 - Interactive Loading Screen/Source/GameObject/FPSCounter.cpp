#include "pch.h"
#include "FPSCounter.h"

#include "BaseRunner.h"

#include <SFML/Graphics.hpp>

namespace IET
{
	FPSCounter::FPSCounter() : AGameObject("FPSCounter")
	{
		updateClock.start();
	}

	FPSCounter::~FPSCounter()
	{
		delete this->statsText;
		AGameObject::~AGameObject();
	}

	void FPSCounter::initialize()
	{
		sf::Font* font = new sf::Font();
		if (font->openFromFile("Source/Media/Kazesawa-Regular.ttf"))
		{

		}

		this->statsText = new sf::Text(*font);
		this->statsText->setPosition({ BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70 });
		this->statsText->setOutlineColor(sf::Color(1, 1, 1));
		this->statsText->setOutlineThickness(2.5f);
		this->statsText->setCharacterSize(35);
	}

	void FPSCounter::processInput(Event event)
	{
	}

	void FPSCounter::update(sf::Time deltaTime)
	{
		this->updateFPS(deltaTime);
	}

	void FPSCounter::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
	{
		AGameObject::draw(renderTarget, renderStates);

		if (this->statsText != nullptr)
			renderTarget.draw(*this->statsText, renderStates);
	}

	void FPSCounter::updateFPS(sf::Time elapsedTime)
	{
		if (updateClock.getElapsedTime().asSeconds() < updateRateSeconds)
			return;

		const float fps = 1.f / elapsedTime.asSeconds();
		//std::cout << floor(fps) << "\n";

		this->statsText->setString("FPS: " + std::to_string(static_cast<int>(fps)));
		updateClock.restart();
		/*this->updateTime += elapsedTime;
		if (this->updateTime >= sf::seconds(0.25f))
		{
			this->updateTime = sf::seconds(0.0f);
			this->statsText->setString("FPS: " + std::to_string(BaseRunner::getInstance()->getFPS()) + "\n");

		}*/
	}
}
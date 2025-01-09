#include "pch.h"
#include "FPSCounter.h"

#include "BaseRunner.h"

FPSCounter::FPSCounter(): AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	if (font->openFromFile("Source/Media/Sansation.ttf"))
	{
		
	}

	this->statsText = new sf::Text(*font);
	this->statsText->setPosition({ BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70 });
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
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

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	float fps = 1.f / elapsedTime.asSeconds();
	this->statsText->setString("FPS: " + std::to_string(static_cast<int>(floor(fps))) +"\n");
}

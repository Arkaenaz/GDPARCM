#include "pch.h"
#include "BackgroundObject.h"

#include "BaseRunner.h"

namespace IET {
	BackgroundObject::BackgroundObject(std::string name) : AGameObject(name)
	{
	}

	void BackgroundObject::initialize()
	{
		Debug::Log(this, "Initializing BackgroundObject...");
		Debug::Log(this, "Declared as " + this->getName());

		//sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
		sf::Texture* texture = new sf::Texture("Source/Media/Textures/Desert.png");
		texture->setRepeated(true);

		this->sprite = new sf::Sprite(*texture);

		this->sprite->setTextureRect(sf::IntRect({ { 0, 0 }, { BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 8} }));
		this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
	}

	void BackgroundObject::processInput(const Event event)
	{
	}

	void BackgroundObject::update(sf::Time deltaTime)
	{
		sf::Vector2f position = this->getPosition();
		position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();
		this->setPosition(position.x, position.y);

		sf::Vector2f localPos = this->sprite->getPosition();
		if (localPos.y * deltaTime.asSeconds() > 0) {
			//reset position
			this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
		}
		else {

		}
	}
}

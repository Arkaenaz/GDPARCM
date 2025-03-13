#include "pch.h"
#include "ScrollingBackground.h"

#include "BaseRunner.h"
#include "Utility/FileUtility.h"

namespace IET
{
	ScrollingBackground::ScrollingBackground(std::string name) : AGameObject(std::move(name))
	{
	}

	void ScrollingBackground::initialize()
	{
		Debug::Log(this, "Initializing ScrollingBackground...");
		Debug::Log(this, "Declared as " + this->getName());

		//sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
		sf::Texture* texture = new sf::Texture(FileUtility::getFileFromTextures("Desert.png"));
		texture->setRepeated(true);

		this->sprite = new sf::Sprite(*texture);

		this->sprite->setTextureRect(sf::IntRect({ { 0, 0 }, { BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 8} }));
		this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
	}

	void ScrollingBackground::processInput(const Event event)
	{
	}

	void ScrollingBackground::update(sf::Time deltaTime)
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

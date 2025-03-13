#include "pch.h"
#include "SpriteObject.h"

#include "BaseRunner.h"
#include "TextureManager.h"
#include "Utility/FileUtility.h"

namespace IET {
	SpriteObject::SpriteObject(std::string name, sf::Texture* texture)
		: AGameObject(std::move(name)), texture(std::move(texture))
	{
	}

	void SpriteObject::initialize()
	{
		Debug::Log(this, "Initializing SpriteObject...");
		Debug::Log(this, "Declared as " + this->getName());

		this->sprite = new sf::Sprite(*texture);
		
	}

	void SpriteObject::processInput(const Event event)
	{
	}

	void SpriteObject::update(sf::Time deltaTime)
	{
		/*sf::Vector2f position = this->getPosition();
		position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();
		this->setPosition(position.x, position.y);

		sf::Vector2f localPos = this->sprite->getPosition();
		if (localPos.y * deltaTime.asSeconds() > 0) {
			//reset position
			this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
		}
		else {

		}*/
	}

	void SpriteObject::setAlpha(uint8_t a)
	{
		this->sprite->setColor({ 255, 255, 255, a });
	}

	uint8_t SpriteObject::getAlpha()
	{
		return this->sprite->getColor().a;
	}
}

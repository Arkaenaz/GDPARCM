#include "pch.h"
#include "AGameObject.h"

namespace IET {
	AGameObject::AGameObject(std::string name) : name(std::move(name))
	{
		this->enabled = true;
	}

	AGameObject::~AGameObject()
	{
		delete this->sprite;
	}

	std::string AGameObject::getName()
	{
		return this->name;
	}

	bool AGameObject::isEnabled() const
	{
		return this->enabled;
	}

	void AGameObject::setEnabled(const bool enabled)
	{
		this->enabled = enabled;
	}

	void AGameObject::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
	{
		if (this->sprite != nullptr)
		{
			this->sprite->setPosition({ this->posX, this->posY });
			this->sprite->setScale({ this->scaleX, this->scaleY });
			renderTarget.draw(*this->sprite, renderStates);
		}
	}

	void AGameObject::setPosition(float x, float y)
	{
		this->posX = x;
		this->posY = y;
	}

	void AGameObject::setPosition(sf::Vector2f position)
	{
		this->posX = position.x;
		this->posY = position.y;
	}

	void AGameObject::setScale(float x, float y)
	{
		this->scaleX = x;
		this->scaleY = y;
	}

	void AGameObject::setScale(float scale)
	{
		this->scaleX = scale;
		this->scaleY = scale;
	}

	sf::Vector2f AGameObject::getPosition()
	{
		return sf::Vector2f(this->posX, this->posY);
	}

	sf::Vector2f AGameObject::getScale()
	{
		return sf::Vector2f(this->scaleX, this->scaleY);
	}

	sf::Sprite* AGameObject::getSprite()
	{
		return this->sprite;
	}

	void AGameObject::setAlpha(uint8_t a)
	{
		this->sprite->setColor({ 255, 255, 255, a });
	}

	uint8_t AGameObject::getAlpha()
	{
		return this->sprite->getColor().a;
	}
}

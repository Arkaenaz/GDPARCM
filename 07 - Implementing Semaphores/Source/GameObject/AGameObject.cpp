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
			//this->sprite->setPosition({ this->posX, this->posY });
			//this->sprite->setScale({ this->scaleX, this->scaleY });
			renderTarget.draw(*this->sprite, renderStates);
		}
	}

	void AGameObject::setPosition(float x, float y)
	{
		this->posX = x;
		this->posY = y;

		if (this->sprite != nullptr)
		{
			this->sprite->setPosition({ this->posX, this->posY });
		}
	}

	void AGameObject::setScale(float x, float y)
	{
		this->scaleX = x;
		this->scaleY = y;

		if (this->sprite != nullptr)
		{
			this->sprite->setScale({ this->scaleX, this->scaleY });
		}
	}

	void AGameObject::setScale(float scale)
	{
		this->scaleX = scale;
		this->scaleY = scale;

		if (this->sprite != nullptr)
		{
			this->sprite->setScale({ this->scaleX, this->scaleY });
		}
	}

	sf::Vector2f AGameObject::getPosition()
	{
		return sf::Vector2f(this->posX, this->posY);
	}

	sf::Vector2f AGameObject::getScale()
	{
		return sf::Vector2f(this->scaleX, this->scaleY);
	}
}
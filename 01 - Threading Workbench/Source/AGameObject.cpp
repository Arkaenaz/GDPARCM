#include "pch.h"
#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->enabled = true;
}

AGameObject::~AGameObject()
{
	delete this->sprite;
	delete this->texture;
}

std::string AGameObject::getName()
{
	return this->name;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}

void AGameObject::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void AGameObject::draw(sf::RenderWindow* targetWindow)
{
	if (this->sprite != nullptr)
	{
		this->sprite->setPosition({ this->posX, this->posY });
		this->sprite->setScale({ this->scaleX, this->scaleY } );
		targetWindow->draw(*this->sprite);
	}
}

void AGameObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if(this->sprite != nullptr)
	{
		this->sprite->setPosition({ this->posX, this->posY } );
	}
}

void AGameObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setScale({ this->scaleX, this->scaleY } );
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
	return this->sprite->getPosition();
}

sf::Vector2f AGameObject::getScale()
{
	return this->sprite->getScale();
}

sf::FloatRect AGameObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}
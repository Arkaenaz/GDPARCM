#include "pch.h"
#include "BackgroundObject.h"

#include "BaseRunner.h"

BackgroundObject::BackgroundObject(std::string name) : AGameObject(name)
{
}

void BackgroundObject::initialize()
{
	//sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	sf::Texture* texture = new sf::Texture("Source/Media/Textures/Desert.png");
	texture->setRepeated(true);

	this->sprite = new sf::Sprite(*texture);

	this->sprite->setTextureRect(sf::IntRect({ { 0, 0 }, { BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 8} }));
	this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
}

void BackgroundObject::processInput(const std::optional<sf::Event>)
{
}

void BackgroundObject::update(sf::Time deltaTime)
{
	sf::Vector2f position = this->getPosition();
	position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();
	this->setPosition(position.x, position.y);

	if (position.y * deltaTime.asSeconds() > 0)
	{
		this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
	}
}

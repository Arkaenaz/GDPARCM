#include "pch.h"
#include "IconObject.h"

#include "TextureManager.h"

IconObject::IconObject(std::string name, int textureIndex) : AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getStreamTexture(this->textureIndex);
	if (texture == nullptr)
		return;
	this->sprite = new sf::Sprite(*texture);
}

void IconObject::processInput(const Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}
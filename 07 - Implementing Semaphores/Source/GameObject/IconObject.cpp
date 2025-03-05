#include "pch.h"
#include "IconObject.h"

#include "TextureManager.h"

namespace IET {
	IconObject::IconObject(String name, int textureIndex) : AGameObject(name)
	{
		this->textureIndex = textureIndex;
	}

	void IconObject::initialize()
	{
		const sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
		this->sprite = new sf::Sprite(*texture);
		this->sprite->setTexture(*texture);
	}

	void IconObject::processInput(const Event event)
	{
	}

	void IconObject::update(sf::Time deltaTime)
	{
	}
}

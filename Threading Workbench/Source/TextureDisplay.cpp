#include "pch.h"
#include "TextureDisplay.h"

#include "TextureManager.h"
#include "GameObjectManager.h"
#include "IconObject.h"

TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	
}

void TextureDisplay::initialize()
{
	
}

void TextureDisplay::processInput(const Event event)
{
	
}

void TextureDisplay::update(sf::Time deltaTime)
{
	this->ticks += deltaTime.asMilliseconds();

	if (this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->iconCount);
		this->iconCount++;
		this->spawnObject();
	}
}

void TextureDisplay::spawnObject()
{
	int IMG_WIDTH = 68;
	int IMG_HEIGHT = 68;

	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;

	std::string objectName = "Icon_" + std::to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	iconObj->setPosition(x, y);

	this->iconList.push_back(iconObj);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);
}

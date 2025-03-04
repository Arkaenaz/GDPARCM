#include "pch.h"
#include "TextureDisplay.h"

#include "BaseRunner.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "IconObject.h"

namespace IET {
	TextureDisplay::TextureDisplay() : AGameObject("TextureDisplay")
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
		this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
		if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY)
		{
			this->startedStreaming = true;
			this->ticks = 0.0f;
			TextureManager::getInstance()->loadStreamingAssets();
		}
		else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY)
		{
			this->ticks = 0.0f;
			TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
			this->numDisplayed++;
		}
	}

	void TextureDisplay::onFinishedExecution()
	{
		this->spawnObject(); //executes spawn once the texture is ready.
	}

	void TextureDisplay::spawnObject()
	{
		this->guard.lock();

		String objectName = "Icon_" + std::to_string(this->iconList.size());
		IconObject* iconObj = new IconObject(objectName, static_cast<int>(this->iconList.size()));
		this->iconList.push_back(iconObj);

		//set position
		int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
		float x = static_cast<float>(this->columnGrid * IMG_WIDTH);
		float y = static_cast<float>(this->rowGrid * IMG_HEIGHT);
		iconObj->setPosition(x, y);

		//std::cout << "Set position: " << x << " " << y << std::endl;

		this->columnGrid++;
		if (this->columnGrid == this->MAX_COLUMN)
		{
			this->columnGrid = 0;
			this->rowGrid++;
		}
		GameObjectManager::getInstance()->addObject(iconObj);

		this->guard.unlock();
	}
}
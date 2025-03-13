#include "pch.h"
#include "TextureDisplay.h"

#include "BaseRunner.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "LoadingDisplay.h"
#include "Utility/FileUtility.h"

namespace IET {
	TextureDisplay::TextureDisplay() : AGameObject("TextureDisplay")
	{
		iconList.reserve(4096);
	}

	void TextureDisplay::initialize()
	{
		this->music = new sf::Music(FileUtility::getFileFromAssets("Audio/Something.mp3"));
		this->loadingDisplay = new LoadingDisplay();
		GameObjectManager::getInstance()->addObject(this->loadingDisplay);

	}

	void TextureDisplay::processInput(const Event event)
	{

	}

	void TextureDisplay::update(sf::Time deltaTime)
	{
		if (!isLoadingFinished)
		{
			this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
			if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY)
			{
				this->ticks = 0.0f;
				TextureManager::getInstance()->loadSingleVideoStreamAsset(this->numDisplayed, this);
				this->numDisplayed++;
			}

			this->isLoadingFinished = !this->loadingDisplay->isEnabled();
			if (this->isLoadingFinished)
				this->ticks = 0.0f;
			return;
		}
		if (currentFrame == 1)
			this->music->play();
		/*this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
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
		}*/

		// Increment Icon
		this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
		if (this->ticks >= 29.97f) {

			currentFrame++;
			if (currentFrame >= iconList.size())
			{
				return;
			}
			this->previousIcon = this->currentIcon;
			this->currentIcon = this->iconList[currentFrame];
			this->currentIcon->setEnabled(true);
			if (this->previousIcon != nullptr)
			{
				this->previousIcon->setEnabled(false);
			}
		}
	}

	void TextureDisplay::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
	{
		for (const auto icon : iconList)
		{
			if (icon->isEnabled())
				icon->draw(renderTarget, sf::RenderStates::Default);
		}
	}

	void TextureDisplay::onFinishedExecution()
	{
		this->spawnObject(); //executes spawn once the texture is ready.
		this->loadingDisplay->setLoaded(this->iconList.size());
		if (this->iconList.size() >= TextureManager::getInstance()->getVideoStreamingAssets())
		{
			this->loadingDisplay->startFadeOut();
		}
	}

	void TextureDisplay::spawnObject()
	{
		this->guard.lock();

		String objectName = "Frame_" + std::to_string(this->iconList.size());
		IconObject* iconObj = new IconObject(std::move(objectName), static_cast<int>(this->iconList.size()));
		iconObj->initialize();
		iconObj->setEnabled(false);
		this->iconList.push_back(iconObj);
		/*String objectName = "Icon_" + std::to_string(this->iconList.size());
		IconObject* iconObj = new IconObject(std::move(objectName), static_cast<int>(this->iconList.size()));
		iconObj->initialize();
		this->iconList.push_back(iconObj);

		//set position
		constexpr int IMG_WIDTH = 68; constexpr int IMG_HEIGHT = 68;
		const float x = static_cast<float>(this->columnGrid * IMG_WIDTH);
		const float y = static_cast<float>(this->rowGrid * IMG_HEIGHT);
		iconObj->setPosition(x, y);

		//std::cout << "Set position: " << x << " " << y << std::endl;

		this->columnGrid++;
		if (this->columnGrid == this->MAX_COLUMN)
		{
			this->columnGrid = 0;
			this->rowGrid++;
		}
		//GameObjectManager::getInstance()->addObject(iconObj);
		*/

		this->guard.unlock();
	}
}

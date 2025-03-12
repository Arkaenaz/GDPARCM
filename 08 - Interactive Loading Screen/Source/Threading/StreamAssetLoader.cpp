#include "pch.h"
#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "GameObject/TextureManager.h"
#include "Utility/StringUtility.h"
#include "Interfaces/IExecutionEvent.h"

namespace IET {
	StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
	{
		this->path = path;
		this->execEvent = executionEvent;
	}

	StreamAssetLoader::~StreamAssetLoader()
	{
		//std::cout << "Destroying stream asset loader. " << std::endl;
	}

	void StreamAssetLoader::onStartTask()
	{
		//std::cout << "Running stream asset loader " << std::endl;
		//simulate loading of very large file
		//std::random_device seeder;
		//std::mt19937 engine(seeder());
		//std::uniform_int_distribution<int> dist(1000, 4000);
		IETThread::sleep(1000);

		std::vector<String> tokens = StringUtility::split(path, '/');
		String assetName = StringUtility::split(tokens[tokens.size() - 1], '.')[0];

		TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

		std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

		this->execEvent->onFinishedExecution();
		//delete after being done
		delete this;
	}
}
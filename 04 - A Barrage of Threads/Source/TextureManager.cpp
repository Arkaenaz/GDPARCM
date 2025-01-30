#include "pch.h"
#include "TextureManager.h"

#include "StreamAssetLoader.h"
#include "Threading/IETThread.h"
#include "Utility/StringUtility.h"

namespace IET {
	TextureManager::TextureManager()
	{
		this->countStreamingAssets();
	}

	void TextureManager::loadFromAssetList()
	{
		std::cout << "[TextureManager] Reading from asset list" << std::endl;
		std::ifstream stream("Media/assets.txt");
		String path;

		while (std::getline(stream, path))
		{
			std::vector<String> tokens = StringUtility::split(path, '/');
			String assetName = StringUtility::split(tokens[tokens.size() - 1], '.')[0];
			this->instantiateAsTexture(path, assetName, false);
			std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
		}
	}

	void TextureManager::loadStreamingAssets()
	{
		for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
			//simulate loading of very large file
			IETThread::sleep(200);

			String path = entry.path().generic_string();
			std::vector<String> tokens = StringUtility::split(path, '/');
			String assetName = StringUtility::split(tokens[tokens.size() - 1], '.')[0];
			this->instantiateAsTexture(path, assetName, true);

			std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
		}
	}

	void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
	{
		int fileNum = 0;

		for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
			if (index == fileNum)
			{
				String path = entry.path().generic_string();
				StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
				assetLoader->start();

				break;
			}

			fileNum++;
		}
	}

	sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
	{
		if (!textureMap[assetName].empty()) {
			return textureMap[assetName][frameIndex];
		}
		else {
			std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
			return nullptr;
		}
	}

	int TextureManager::getNumFrames(const String assetName)
	{
		if (!textureMap[assetName].empty()) {
			return static_cast<int>(textureMap[assetName].size());
		}
		else {
			std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
			return 0;
		}
	}

	sf::Texture* TextureManager::getStreamTextureFromList(const int index)
	{
		return streamTextureList[index];
	}

	int TextureManager::getNumLoadedStreamTextures() const
	{
		return static_cast<int>(streamTextureList.size());
	}

	void TextureManager::countStreamingAssets()
	{
		streamingAssetCount = 0;
		for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
			streamingAssetCount++;
		}
		std::cout << "[TextureManager] Number of streaming assets: " << streamingAssetCount << std::endl;
	}

	void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
	{
		sf::Texture* texture = new sf::Texture();
		if (texture->loadFromFile(path))
		{
			// Error
		}
		textureMap[assetName].push_back(texture);

		if (isStreaming)
		{
			streamTextureList.push_back(texture);
		}
		else
		{
			baseTextureList.push_back(texture);
		}

	}
}
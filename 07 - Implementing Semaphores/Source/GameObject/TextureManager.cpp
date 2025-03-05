#include "pch.h"
#include "TextureManager.h"

#include "Threading/StreamAssetLoader.h"
#include "Threading/IETThread.h"
#include "Utility/StringUtility.h"

namespace IET {
	TextureManager::TextureManager()
	{
		this->countStreamingAssets();
		this->threadPool = new ThreadPool("Texture Manager Thread Pool", 8);
		this->threadPool->startScheduler();
	}

	void TextureManager::loadFromAssetList()
	{
		Debug::Log(this, "Reading from asset list");
		std::ifstream stream("Media/assets.txt");
		String path;

		while (std::getline(stream, path))
		{
			std::vector<String> tokens = StringUtility::split(path, '/');
			String assetName = StringUtility::split(tokens[tokens.size() - 1], '.')[0];
			this->instantiateAsTexture(path, assetName, false);
			Debug::Log(this, "Loaded texture: " + assetName);
		}
	}

	void TextureManager::loadStreamingAssets()
	{
		for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
		{
			//simulate loading of very large file
			IETThread::sleep(200);

			String path = entry.path().generic_string();
			std::vector<String> tokens = StringUtility::split(path, '/');
			String assetName = StringUtility::split(tokens[tokens.size() - 1], '.')[0];
			this->instantiateAsTexture(path, assetName, true);

			Debug::Log(this, "Loaded streaming texture: " + assetName);
		}
	}

	void TextureManager::loadSingleStreamAsset(const int index, IExecutionEvent* executionEvent)
	{
		int fileNum = 0;

		for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
		{
			if (index == fileNum)
			{
				const String path = entry.path().generic_string();
				StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
				this->threadPool->scheduleTask(assetLoader);

				break;
			}

			fileNum++;
		}
	}

	sf::Texture* TextureManager::getFromTextureMap(const String& assetName, int frameIndex)
	{
		if (!this->textureMap[assetName].empty())
		{
			return this->textureMap[assetName][frameIndex];
		}

		Debug::Log(this, "No texture found for " + assetName);
		return nullptr;
	}

	int TextureManager::getNumFrames(const String& assetName)
	{
		if (!this->textureMap[assetName].empty())
		{
			return static_cast<int>(this->textureMap[assetName].size());
		}

		Debug::Log(this, "No texture found for " + assetName);
		return 0;
	}

	sf::Texture* TextureManager::getStreamTextureFromList(const int index) const
	{
		return this->streamTextureList[index];
	}

	int TextureManager::getNumLoadedStreamTextures() const
	{
		return static_cast<int>(this->streamTextureList.size());
	}

	void TextureManager::countStreamingAssets()
	{
		streamingAssetCount = 0;
		for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
		{
			streamingAssetCount++;
		}

		Debug::Log(this, "Number of streaming assets: " + streamingAssetCount);
	}

	void TextureManager::instantiateAsTexture(const String& path, const String& assetName, bool isStreaming)
	{
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(path))
		{
			Debug::LogError("Texture not found from path: " + path);
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
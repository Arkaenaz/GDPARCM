#include "pch.h"
#include "TextureManager.h"

#include "StringUtility.h"

TextureManager* TextureManager::P_SHARED_INSTANCE = nullptr;
TextureManager* TextureManager::getInstance()
{
	if (P_SHARED_INSTANCE == nullptr)
	{
		P_SHARED_INSTANCE = new TextureManager();
	}

	return P_SHARED_INSTANCE;
}

void TextureManager::loadAssets()
{

}

void TextureManager::loadSingleStreamAsset(int index)
{
	int fileNum = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			std::string path = entry.path().generic_string();
			std::vector<std::string> stringSplit = StringUtility::split(path, '/');
			std::string assetName = StringUtility::split(stringSplit[stringSplit.size() - 1], '.')[0];
			this->instantiateTexture(path, assetName, true);

			std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
		}
		fileNum++;
	}
}

sf::Texture* TextureManager::getStreamTexture(const int index)
{
	return this->streamTextureList[index];
}

void TextureManager::instantiateTexture(std::string path, std::string assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	if (isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}

}
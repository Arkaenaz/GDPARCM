#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<std::string, TextureList> TextureMap;

	static TextureManager* getInstance();

	void loadAssets();
	void loadSingleStreamAsset(int index);
	sf::Texture* getStreamTexture(int index);
	void instantiateTexture(std::string path, std::string assetName, bool isStreaming);

private:
	TextureManager() = default;
	TextureManager(TextureManager const&) {}
	TextureManager& operator=(TextureManager const&) {}

	static TextureManager* P_SHARED_INSTANCE;

	TextureMap textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;

	const std::string STREAMING_PATH = "Source/Media/Streaming/";
};
#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Interfaces/IExecutionEvent.h"
#include "Interfaces/Singleton.h"

namespace IET
{
	class TextureManager : public Singleton<TextureManager>
	{
	public:
		typedef std::vector<sf::Texture*> TextureList;
		typedef std::unordered_map<String, TextureList> TextureMap;

		void loadFromAssetList(); //loading of all assets needed for startup
		void loadStreamingAssets(); //loading of assets during runtime
		void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
		sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
		int getNumFrames(const String assetName);

		sf::Texture* getStreamTextureFromList(const int index);
		int getNumLoadedStreamTextures() const;

		void instantiateAsTexture(String path, String assetName, bool isStreaming);

	private:
		friend class Singleton;

		TextureManager();
		void countStreamingAssets();

		const std::string STREAMING_PATH = "Source/Media/Streaming/";

		TextureMap textureMap;
		TextureList baseTextureList;
		TextureList streamTextureList;

		int streamingAssetCount = 0;
	};
}

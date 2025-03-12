#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Threading/ThreadPool.h"
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
		void loadSingleStreamAsset(const int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
		void loadSingleVideoStreamAsset(const int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
		sf::Texture* getFromTextureMap(const String& assetName, int frameIndex);
		int getNumFrames(const String& assetName);

		sf::Texture* getStreamTextureFromList(const int index) const;
		sf::Texture* getVideoStreamTextureFromList(const int index) const;
		int getNumLoadedStreamTextures() const;
		int getNumLoadedVideoStreamTextures() const;

		void instantiateAsTexture(const String& path, const String& assetName, bool isStreaming);

	private:
		friend class Singleton;

		TextureManager();
		void countStreamingAssets();

		const std::string STREAMING_PATH = "Source/Media/Streaming/";
		const std::string VIDEO_STREAMING_PATH = "Source/Media/Video Streaming/";

		ThreadPool* threadPool;

		TextureMap textureMap;
		TextureList baseTextureList;
		TextureList streamTextureList;
		TextureList videoStreamTextureList;

		int streamingAssetCount = 0;
	};
}

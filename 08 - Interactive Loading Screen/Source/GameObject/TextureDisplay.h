#pragma once

#include "AGameObject.h"
#include "Interfaces/IExecutionEvent.h"

namespace IET {
	class IconObject;
	class LoadingDisplay;
	class TextureDisplay : public AGameObject, public IExecutionEvent
	{
	public:
		TextureDisplay();
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) override;

		void onFinishedExecution() override;

	private:
		LoadingDisplay* loadingDisplay;
		sf::Music* music;

		typedef std::vector<IconObject*> IconList;
		IconList iconList;

		int currentFrame = -1;
		IconObject* currentIcon = nullptr;
		IconObject* previousIcon = nullptr;

		enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };

		const float STREAMING_LOAD_DELAY = 50;
		const StreamingType streamingType = SINGLE_STREAM;

		Mutex guard; //used to avoid possible race conditions when spawning objects. Not really required for this exercise. Will be explained in future lessons.

		float ticks = 0.0f;
		bool startedStreaming = false;

		int columnGrid = 0;
		int rowGrid = 0;
		int numDisplayed = 0;

		const int MAX_COLUMN = 28;
		const int MAX_ROW = 22;

		
		void spawnObject();

		bool isLoadingFinished = false;
	};
}

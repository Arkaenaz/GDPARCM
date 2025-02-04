#pragma once

#include "AGameObject.h"
#include "Interfaces/IExecutionEvent.h"

namespace IET {
	class IconObject;
	class TextureDisplay : public AGameObject, public IExecutionEvent
	{
	public:
		TextureDisplay();
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;

		void onFinishedExecution() override;

	private:
		typedef std::vector<IconObject*> IconList;

		IconList iconList;

		enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };

		const float STREAMING_LOAD_DELAY = 0.01f;
		const StreamingType streamingType = SINGLE_STREAM;

		float ticks = 0.0f;
		bool startedStreaming = false;

		int columnGrid = 0;
		int rowGrid = 0;
		int numDisplayed = 0;

		const int MAX_COLUMN = 28;
		const int MAX_ROW = 22;

		Mutex guard; //used to avoid possible race conditions when spawning objects. Not really required for this exercise. Will be explained in future lessons.
		void spawnObject();
	};
}

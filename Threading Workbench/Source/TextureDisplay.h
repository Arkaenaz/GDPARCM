#pragma once

#include "AGameObject.h"

class IconObject;
class TextureDisplay: public AGameObject
{
public:
	TextureDisplay();
	void initialize() override;
	void processInput(Event event) override;
	void update(sf::Time deltaTime) override;

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;
	int iconCount = 0;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 4000.0f;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0;
	int rowGrid = 0;
	
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();
};


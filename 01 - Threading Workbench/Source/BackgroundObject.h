#pragma once

#include "AGameObject.h"

class BackgroundObject : public AGameObject
{
public:
	BackgroundObject(std::string name);
	void initialize() override;
	void processInput(Event event) override;
	void update(sf::Time deltaTime) override;

private:
	const float SPEED_MULTIPLIER = 100.0f;
};


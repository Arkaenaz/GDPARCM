#pragma once

#include "AGameObject.h"

class IconObject : public AGameObject
{
public:
	IconObject(std::string name, int textureIndex);
	void initialize() override;
	void processInput(Event event) override;
	void update(sf::Time deltaTime) override;

private:
	int textureIndex = 0;
};


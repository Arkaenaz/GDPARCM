#pragma once

#include "AGameObject.h"

namespace IET
{
	class IconObject : public AGameObject
	{
	public:
		IconObject(String name, int textureIndex);
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;

	private:
		int textureIndex = 0;
	};
}
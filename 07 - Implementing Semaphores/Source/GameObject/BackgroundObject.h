#pragma once

#include <SFML/Graphics.hpp>

#include "AGameObject.h"

namespace IET {
	class ScrollingBackground : public AGameObject
	{
	public:
		ScrollingBackground(String name);
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;

	private:
		const float SPEED_MULTIPLIER = 100.0f;

		sf::Texture* texture;
	};
}
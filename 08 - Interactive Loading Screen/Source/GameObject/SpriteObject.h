#pragma once

#include <SFML/Graphics.hpp>

#include "AGameObject.h"

namespace IET {
	class SpriteObject : public AGameObject
	{
	public:
		SpriteObject(String name, sf::Texture* texture);

		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;

		void setAlpha(uint8_t a);
		uint8_t getAlpha();

	private:
		sf::Texture* texture;
	};
}
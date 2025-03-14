#pragma once

#include <SFML/Graphics.hpp>

#include "AGameObject.h"

namespace IET {
	class RectangleObject : public AGameObject
	{
	public:
		RectangleObject(String name);

		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) override;

	private:
		sf::RectangleShape* rectangle;
	};
}
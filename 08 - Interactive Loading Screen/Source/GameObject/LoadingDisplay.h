#pragma once

#include "AGameObject.h"

namespace IET {
	class LoadingDisplay : public AGameObject
	{
		LoadingDisplay();
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) override;
	};
}
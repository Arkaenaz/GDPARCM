#pragma once

#include "AGameObject.h"

namespace IET {
	class FPSCounter : public AGameObject
	{
	public:
		FPSCounter();
		~FPSCounter() override;
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderWindow* targetWindow) override;

	private:
		sf::Time updateTime;
		sf::Text* statsText;

		void updateFPS(sf::Time elapsedTime);
	};
}
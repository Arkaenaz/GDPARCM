#pragma once

#include "AGameObject.h"

namespace IET {
	class FPSCounter final : public AGameObject
	{
	public:
		FPSCounter();
		~FPSCounter() override;
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default) override;

	private:
		sf::Time updateTime;
		sf::Text* statsText;

		void updateFPS(sf::Time elapsedTime);

		sf::Clock updateClock;
		float updateRateSeconds = 0.5f;
	};
}
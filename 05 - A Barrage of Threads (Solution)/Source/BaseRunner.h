#pragma once

#include <SFML/Graphics.hpp>

#include "Interfaces/NonCopyable.h"
#include "Interfaces/Singleton.h"

namespace IET {
	class BaseRunner : public Singleton<BaseRunner>, NonCopyable
	{
	public:
		static const sf::Time		TIME_PER_FRAME;
		static const float			GAME_SPEED;
		static constexpr unsigned	FRAME_RATE_LIMIT = 60;
		static constexpr int		WINDOW_WIDTH = 1920;
		static constexpr int		WINDOW_HEIGHT = 1080;

		BaseRunner();
		void run();

		float getFPS() const;

	private:
		sf::RenderWindow			window;
		float fps = 0.0f;

		void render();
		void processEvents();
		void update(sf::Time elapsedTime);
	};
}

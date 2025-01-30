#pragma once

#include <SFML/Graphics.hpp>

class BaseRunner
{
public:
	static const sf::Time		TIME_PER_FRAME;
	static const float			GAME_SPEED;
	static constexpr unsigned	FRAME_RATE_LIMIT = 60;
	static constexpr int		WINDOW_WIDTH	 = 1920;
	static constexpr int		WINDOW_HEIGHT	 = 1080;

	BaseRunner();
	BaseRunner(const BaseRunner&) = delete;
	BaseRunner& operator=(const BaseRunner&) = delete;
	void run();

private:
	
	sf::RenderWindow		window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};



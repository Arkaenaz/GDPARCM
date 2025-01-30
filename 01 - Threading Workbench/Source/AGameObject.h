#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class AGameObject
{
	public:
		AGameObject(std::string name);
		virtual ~AGameObject();
		AGameObject(const AGameObject&) = delete;
		AGameObject& operator=(const AGameObject&) = delete;

		virtual void initialize() = 0;
		virtual void processInput(Event event) = 0;
		virtual void update(sf::Time deltaTime) = 0;
		virtual void draw(sf::RenderWindow* targetWindow);

		std::string getName();

		bool isEnabled();
		void setEnabled(bool enabled);

		virtual void setPosition(float x, float y);
		virtual void setScale(float x, float y);
		virtual void setScale(float scale);

		virtual sf::FloatRect getLocalBounds();
		virtual sf::Vector2f getPosition();
		virtual sf::Vector2f getScale();

	protected:
		bool enabled;

		std::string name;
		sf::Sprite* sprite;
		sf::Texture* texture;

		float posX = 0.0f; float posY = 0.0f;
		float scaleX = 1.0f; float scaleY = 1.0f;
};


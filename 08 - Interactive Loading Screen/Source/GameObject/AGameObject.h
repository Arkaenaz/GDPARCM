#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Interfaces/NonCopyable.h"

namespace IET {
	class AComponent;
	class AGameObject : public NonCopyable
	{
	public:
		explicit AGameObject(String name);
		virtual ~AGameObject();

		virtual void initialize() = 0;
		virtual void processInput(Event event) = 0;
		virtual void update(const sf::Time deltaTime) = 0;
		virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default);

		String getName();

		bool isEnabled() const;
		void setEnabled(const bool enabled);
		
		virtual void setPosition(float x, float y);
		virtual void setPosition(sf::Vector2f position);
		virtual void setScale(float x, float y);
		virtual void setScale(float scale);
		
		//virtual sf::FloatRect getLocalBounds();
		virtual sf::Vector2f getPosition();
		virtual sf::Vector2f getScale();

		sf::Sprite* getSprite();
		void setAlpha(uint8_t a);
		uint8_t getAlpha();
	protected:
		bool enabled;

		String name;

		sf::Sprite* sprite;

		float posX = 0.0f; float posY = 0.0f;
		float scaleX = 1.0f; float scaleY = 1.0f;
	};
}

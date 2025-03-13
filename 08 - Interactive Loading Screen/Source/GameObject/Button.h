#pragma once

#include "AGameObject.h"
#include "Interfaces/IButtonListener.h"

namespace IET
{
	class Button : public AGameObject
	{
	public:
		Button(String name, sf::Texture* texture);
		~Button();

		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void changeState();

		void setListener(IButtonListener* listener);
		
	private:
		IButtonListener* listener;
		sf::Texture* texture;

		void processMouseInput(bool pressed, Event event);
		bool contains(sf::Vector2f location);
	};
}


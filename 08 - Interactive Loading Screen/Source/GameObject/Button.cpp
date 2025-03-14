#include "pch.h"
#include "Button.h"

namespace IET
{
	Button::Button(String name, sf::Texture* texture)
		: AGameObject(std::move(name)), texture(texture)
	{
	}

	Button::~Button()
	{
	}

	void Button::initialize()
	{
		this->sprite = new sf::Sprite(*texture);
	}

	void Button::processInput(Event event)
	{
		if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (this->contains(sf::Vector2f(mousePressed->position))) {
				this->listener->onClick(this);
			}
			
		}
		if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (this->contains(sf::Vector2f(mouseReleased->position))) {
				this->listener->onRelease(this);
				this->listener->reset(this);
			}
		}
	}

	void Button::update(sf::Time deltaTime)
	{
	}

	void Button::changeState()
	{
	}

	void Button::setListener(IButtonListener* listener)
	{
		this->listener = listener;
	}

	bool Button::contains(sf::Vector2f location)
	{
		if (this->getSprite()->getGlobalBounds().contains(location))
		{
			return true;
		}
		return false;
	}
}

#include "pch.h"
#include "RectangleObject.h"

#include "BaseRunner.h"


namespace IET {
	RectangleObject::RectangleObject(String name)
		: AGameObject(std::move(name))
	{
	}

	void RectangleObject::initialize()
	{
		this->rectangle = new sf::RectangleShape(sf::Vector2f(BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));
		this->rectangle->setFillColor(sf::Color(0, 0, 0 ,100));
	}

	void RectangleObject::processInput(Event event)
	{
	}

	void RectangleObject::update(sf::Time deltaTime)
	{
	}

	void RectangleObject::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
	{
		AGameObject::draw(renderTarget, renderStates);
		renderTarget.draw(*this->rectangle, renderStates);
	}
}

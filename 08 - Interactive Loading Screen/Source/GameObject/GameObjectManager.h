#pragma once

#include <vector>
#include <unordered_map>

#include "AGameObject.h"

#include <SFML/Graphics.hpp>

#include "Interfaces/Singleton.h"

namespace IET {
	typedef std::vector<AGameObject*> GameObjectList;
	typedef std::unordered_map<std::string, AGameObject*> GameObjectMap;

	class GameObjectManager : public Singleton<GameObjectManager>
	{
	public:
		AGameObject* findObjectByName(std::string name);

		GameObjectList getAllObjects();
		int activeObjects();

		void processInput(IET::Event event);
		void update(sf::Time deltaTime);
		void draw(sf::RenderWindow* window);

		void addObject(AGameObject* gameObject);
		void deleteObject(AGameObject* gameObject);
		void deleteObjectByName(std::string name);

	private:
		friend class Singleton;

		GameObjectManager();

		GameObjectMap gameObjectMap;
		GameObjectList gameObjectList;

		Mutex guard;
	};
}

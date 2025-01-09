#pragma once

#include <vector>
#include <unordered_map>

#include "AGameObject.h"

#include <SFML/Graphics.hpp>

class GameObjectManager
{
	public:
		typedef std::vector<AGameObject*> GameObjectList;
		typedef std::unordered_map<std::string, AGameObject*> GameObjectMap;

		static GameObjectManager* getInstance();
		AGameObject* findObjectByName(std::string name);

		GameObjectList getAllObjects();
		int activeObjects();

		void processInput(Event event);
		void update(sf::Time deltaTime);
		void draw(sf::RenderWindow* window);

		void addObject(AGameObject* gameObject);
		void deleteObject(AGameObject* gameObject);
		void deleteObjectByName(std::string name);

	private:
		GameObjectManager() = default;
		GameObjectManager(GameObjectManager const&) {}
		GameObjectManager& operator=(GameObjectManager const&) {}

		static GameObjectManager* P_SHARED_INSTANCE;

		GameObjectMap gameObjectMap;
		GameObjectList gameObjectList;
};


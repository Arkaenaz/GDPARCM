#include "pch.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::P_SHARED_INSTANCE = nullptr;
GameObjectManager* GameObjectManager::getInstance() {
	if (P_SHARED_INSTANCE == nullptr)
	{
		P_SHARED_INSTANCE = new GameObjectManager();
		P_SHARED_INSTANCE->gameObjectList.reserve(100);
	}

	return P_SHARED_INSTANCE;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return nullptr;
	}
}

std::vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::processInput(const Event event) {
	for (AGameObject* pGameObject : this->gameObjectList)
	{
		if (pGameObject->isEnabled())
			pGameObject->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	for (AGameObject* pGameObject : this->gameObjectList)
	{
		if (pGameObject->isEnabled())
			pGameObject->update(deltaTime);
	}
}

void GameObjectManager::draw(sf::RenderWindow* window) {
	for (AGameObject* pGameObject : this->gameObjectList)
	{
		if (pGameObject->isEnabled())
			pGameObject->draw(window);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->gameObjectMap[gameObject->getName()] = gameObject;
	this->gameObjectList.push_back(gameObject);
	this->gameObjectMap[gameObject->getName()]->initialize();
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
	
	delete gameObject;
}

void GameObjectManager::deleteObjectByName(std::string name) {
	AGameObject* object = this->findObjectByName(name);
	
	if (object != NULL) {
		this->deleteObject(object);
	}
}

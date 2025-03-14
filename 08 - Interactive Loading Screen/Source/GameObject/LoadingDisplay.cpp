#include "pch.h"
#include "LoadingDisplay.h"

#include "Button.h"
#include "SpriteObject.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "TextureManager.h"

#include "Utility/FileUtility.h"
#include "Utility/MathUtility.h"

namespace IET
{
	LoadingDisplay::LoadingDisplay() : AGameObject("LoadingDisplay")
	{
	}

	void LoadingDisplay::initialize()
	{
		this->music = new sf::Music(FileUtility::getFileFromAssets("Audio/Loading.mp3"));
		this->music->play();

		this->buttonClickBuffer = new sf::SoundBuffer(FileUtility::getFileFromAssets("Audio/back-button-click.wav"));
		this->buttonClick = new sf::Sound(*this->buttonClickBuffer);

		for (int i = 0; i < 4; i++) {
			sf::Texture* backgroundTexture = TextureManager::getInstance()->getBackgroundFromList(i);
			SpriteObject* backgroundObject = new SpriteObject("Background_" + std::to_string(i), backgroundTexture);
			GameObjectManager::getInstance()->addObject(backgroundObject);
			backgroundObject->getSprite()->setTextureRect(sf::IntRect({ 0, 0 }, { BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT }));
			backgroundObject->setEnabled(false);
			this->backgroundObjects.push_back(backgroundObject);

			sf::Texture* parallaxTexture = TextureManager::getInstance()->getParallaxFromList(i);
			SpriteObject* parallaxObject = new SpriteObject("Parallax_" + std::to_string(i), parallaxTexture);
			GameObjectManager::getInstance()->addObject(parallaxObject);
			parallaxObject->getSprite()->setTextureRect(sf::IntRect({ 0, 1200 }, { 1920, 1080 }));
			parallaxObject->setScale(0.8f);
			parallaxObject->setPosition(384.f / 2.0f, 216 /2);
			parallaxObject->setEnabled(false);
			this->parallaxObjects.push_back(parallaxObject);
		}

		sf::Texture* arrowTexture = new sf::Texture(FileUtility::getFileFromTextures("arrow.png"));
		leftButton = new Button("Left Arrow", arrowTexture);
		leftButton->setScale(-1.0f, 1.0f);
		leftButton->setPosition(150, (BaseRunner::WINDOW_HEIGHT - 78) / 2);

		rightButton = new Button("Right Arrow", arrowTexture);
		rightButton->setPosition(BaseRunner::WINDOW_WIDTH - 150, (BaseRunner::WINDOW_HEIGHT - 78) / 2);

		leftButton->setListener(this);
		rightButton->setListener(this);

		GameObjectManager::getInstance()->addObject(leftButton);
		GameObjectManager::getInstance()->addObject(rightButton);

		this->glass = new SpriteObject("Glass", new sf::Texture(FileUtility::getFileFromTextures("Glass.png")));
		GameObjectManager::getInstance()->addObject(glass);

		for (int i = 0; i < 4; i++) {
			sf::Texture* characterTexture = TextureManager::getInstance()->getCharacterFromList(i);
			SpriteObject* characterObject = new SpriteObject("Partner_" + std::to_string(i), characterTexture);

			GameObjectManager::getInstance()->addObject(characterObject);
			characterObject->setEnabled(false);
			characterObject->setPosition(600, 400);
			this->characterObjects.push_back(characterObject);
		}

		loadingBar = new SpriteObject("Loading Bar", new sf::Texture(FileUtility::getFileFromTextures("Loading Bar.png")));
		GameObjectManager::getInstance()->addObject(loadingBar);
		loadingBar->setScale(0.0f, 0.2f);

		index = 0;
		value = 0;

		this->currentBackground = this->backgroundObjects[index];
		this->currentBackground->setAlpha(0);
		this->currentBackground->setEnabled(true);

		this->currentParallax = this->parallaxObjects[index];
		this->currentParallax->setAlpha(0);
		this->currentParallax->setEnabled(true);

		this->currentCharacter = this->characterObjects[index];
		this->currentCharacter->setAlpha(0);
		this->currentCharacter->setEnabled(true);

		this->startFadeIn();
		
	}

	void LoadingDisplay::processInput(Event event)
	{
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->code == sf::Keyboard::Key::D)
			{
				if (this->fadeBetween || this->fadingOut)
					return;
				this->buttonClick->play();
				index++;
				if (index >= 4)
				{
					index = 0;
				}
				this->updateAssets();
			}
			if(keyPressed->code == sf::Keyboard::Key::A)
			{
				if (this->fadeBetween || this->fadingOut)
					return;
				this->buttonClick->play();
				index--;
				if (index <= -1)
				{
					index = 3;
				}
				this->updateAssets();
			}
		}
	}

	void LoadingDisplay::update(sf::Time deltaTime)
	{
		// Fade In
		if (this->fadingIn)
		{
			this->value = MathUtility::moveTowards(this->value, 100, deltaTime.asSeconds() * 50);
			this->music->setVolume(this->value);
			this->currentBackground->setAlpha(255 * (this->value / 100));
			this->currentParallax->setAlpha(255 * (this->value / 100));
			this->currentCharacter->setAlpha(255 * (this->value / 100));
			this->leftButton->setAlpha(255 * (this->value / 100));
			this->rightButton->setAlpha(255 * (this->value / 100));
			this->loadingBar->setAlpha(255 * (this->value / 100));
			this->glass->setAlpha(255 * (this->value / 100));

			if (this->value >= 100)
			{
				this->fadingIn = false;
			}
		}
		// Fade Out
		if (this->fadingOut)
		{
			this->value = MathUtility::moveTowards(this->value, 0, deltaTime.asSeconds() * 25);
			this->music->setVolume(this->value);
			this->currentBackground->setAlpha(255 * (this->value / 100));
			this->currentParallax->setAlpha(255 * (this->value / 100));
			this->currentCharacter->setAlpha(255 * (this->value / 100));
			this->leftButton->setAlpha(255 * (this->value / 100));
			this->rightButton->setAlpha(255 * (this->value / 100));
			this->loadingBar->setAlpha(255 * (this->value / 100));
			this->glass->setAlpha(255 * (this->value / 100));

			if (this->value <= 0)
			{
				this->fadingOut = false;
				this->disable();
			}
		}

		// Fade Between Assets
		if (this->fadeBetween)
		{
			this->value = MathUtility::moveTowards(this->value, 100, deltaTime.asSeconds() * 50);

			this->currentBackground->setAlpha(255 * (this->value / 100));
			this->currentParallax->setAlpha(255 * (this->value / 100));
			this->currentCharacter->setAlpha(255 * (this->value / 100));

			if (this->previousBackground != nullptr)
			{
				this->previousBackground->setAlpha(255 * ((100 - this->value) / 100));
			}
			if (this->previousParallax != nullptr)
			{
				this->previousParallax->setAlpha(255 * ((100 - this->value) / 100));
			}
			if (this->previousCharacter != nullptr)
			{
				this->previousCharacter->setAlpha(255 * ((100 - this->value) / 100));
			}

			if (this->value >= 100) {
				this->fadeBetween = false;
				if (this->previousBackground != nullptr)
				{
					this->previousBackground->setEnabled(false);
				}

				if (this->previousParallax != nullptr)
				{
					this->previousParallax->setEnabled(false);
				}

				if (this->previousCharacter != nullptr)
				{
					this->previousCharacter->setEnabled(false);
				}
			}
		}

		this->loadingBar->setScale(static_cast<float>(TextureManager::getInstance()->getNumLoadedVideoStreamTextures()) / static_cast<float>(TextureManager::getInstance()->getVideoStreamingAssets()), 0.2f);

		// Parallax
		const sf::Vector2i mousePosition = sf::Mouse::getPosition(BaseRunner::getInstance()->getWindow());

		const float xOffset = (mousePosition.x - BaseRunner::WINDOW_WIDTH / 2.0f);
		const float yOffset = (mousePosition.y - BaseRunner::WINDOW_HEIGHT / 2.0f);

		constexpr float bgDepthScale = 0.04f;
		constexpr float glassDepthScale = 0.05f;
		constexpr float characterDepthScale = 0.03f;
		constexpr float arrowDepthScale = 0.02f;
		constexpr float lerpSpeed = 100.f;

		const float xBg = BaseRunner::WINDOW_WIDTH / 2.0f - this->currentParallax->getSprite()->getGlobalBounds().size.x / 2.0f;
		const float yBg = BaseRunner::WINDOW_HEIGHT / 2.0f- this->currentParallax->getSprite()->getGlobalBounds().size.y / 2.0f;

		const float glassBgX = BaseRunner::WINDOW_WIDTH / 2.0f - this->glass->getSprite()->getGlobalBounds().size.x / 2.0f;
		const float glassBgY = BaseRunner::WINDOW_HEIGHT / 2.0f - this->glass->getSprite()->getGlobalBounds().size.y / 2.0f;

		const sf::Vector2f offset = { xOffset, yOffset };
		const sf::Vector2f bgOriginalPosition = { xBg, yBg };
		const sf::Vector2f glassOriginalPosition = { glassBgX, glassBgY };
		const sf::Vector2f characterOriginalPosition = { 600, 400 };
		const sf::Vector2f leftArrowOriginalPosition = { 150, (BaseRunner::WINDOW_HEIGHT - 78) / 2 };
		const sf::Vector2f rightArrowOriginalPosition = { BaseRunner::WINDOW_WIDTH - 150, (BaseRunner::WINDOW_HEIGHT - 78) / 2 };

		this->currentParallax->setPosition(MathUtility::moveTowards(this->currentParallax->getPosition(), bgOriginalPosition + offset * bgDepthScale, lerpSpeed * deltaTime.asSeconds()));
		this->currentCharacter->setPosition(MathUtility::moveTowards(this->currentCharacter->getPosition(), characterOriginalPosition + offset * characterDepthScale, lerpSpeed * deltaTime.asSeconds()));
		this->leftButton->setPosition(MathUtility::moveTowards(this->leftButton->getPosition(), leftArrowOriginalPosition + offset * arrowDepthScale, lerpSpeed * deltaTime.asSeconds()));
		this->rightButton->setPosition(MathUtility::moveTowards(this->rightButton->getPosition(), rightArrowOriginalPosition + offset * arrowDepthScale, lerpSpeed * deltaTime.asSeconds()));
		this->glass->setPosition(MathUtility::moveTowards(this->glass->getPosition(), glassOriginalPosition + offset * glassDepthScale, lerpSpeed * deltaTime.asSeconds()));
	}

	void LoadingDisplay::disable()
	{
		this->music->stop();
		this->currentBackground->setEnabled(false);
		this->currentCharacter->setEnabled(false);
		this->setEnabled(false);
	}

	void LoadingDisplay::onClick(Button* pButton)
	{
		if (pButton->getName().find("Left Arrow") != std::string::npos)
		{
			if (this->fadeBetween || this->fadingOut)
				return;
			this->buttonClick->play();
			index--;
			if (index <= -1)
			{
				index = 3;
			}
			this->updateAssets();
		}

		if (pButton->getName().find("Right Arrow") != std::string::npos)
		{
			if (this->fadeBetween || this->fadingOut)
				return;
			this->buttonClick->play();
			index++;
			if (index >= 4)
			{
				index = 0;
			}
			Debug::Log(std::to_string(index));
			this->updateAssets();
		}
	}

	void LoadingDisplay::onHover(Button* pButton)
	{
	}

	void LoadingDisplay::onRelease(Button* pButton)
	{
	}

	void LoadingDisplay::reset(Button* pButton)
	{
	}

	void LoadingDisplay::setLoaded(int loaded)
	{
		this->loaded = loaded;
	}

	void LoadingDisplay::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
	{
		AGameObject::draw(renderTarget, renderStates);
	}

	void LoadingDisplay::updateAssets()
	{
		this->previousBackground = this->currentBackground;
		this->currentBackground = this->backgroundObjects[index];
		this->currentBackground->setPosition(this->previousBackground->getPosition());
		this->currentBackground->setEnabled(true);
		this->currentBackground->setAlpha(0);

		this->previousParallax = this->currentParallax;
		this->currentParallax = this->parallaxObjects[index];
		this->currentParallax->setPosition(this->previousParallax->getPosition());
		this->currentParallax->setEnabled(true);
		this->currentParallax->setAlpha(0);

		this->previousCharacter = this->currentCharacter;
		this->currentCharacter = this->characterObjects[index];
		this->currentCharacter->setPosition(this->previousCharacter->getPosition());
		this->currentCharacter->setEnabled(true);
		this->currentCharacter->setAlpha(0);

		this->startFadeBetweenAssets();
	}

	void LoadingDisplay::startFadeIn()
	{
		this->value = 0;
		this->fadingIn = true;
	}

	void LoadingDisplay::startFadeOut()
	{
		this->value = 100;
		this->fadingOut = true;
	}

	void LoadingDisplay::startFadeBetweenAssets()
	{
		this->value = 0;
		this->fadeBetween = true;
	}
}

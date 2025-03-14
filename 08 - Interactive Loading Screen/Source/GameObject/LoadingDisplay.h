#pragma once

#include "AGameObject.h"
#include "Interfaces/IButtonListener.h"

namespace IET {
	class SpriteObject;
	class RectangleObject;
	class LoadingDisplay : public AGameObject, public IButtonListener
	{
	public:
		LoadingDisplay();
		void initialize() override;
		void processInput(Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) override;

		void updateAssets();
		void updateParallax(sf::Time deltaTime);
		void disableAllAssets();

		void startFadeIn();
		void startFadeOut();
		void startFadeBetweenAssets();

		void fadeAssets(float value);
		void fadeBetweenAssets(float value);

		void onClick(Button* pButton);
		void onHover(Button* pButton);
		void onRelease(Button* pButton);
		void reset(Button* pButton);

		void setNumLoaded(int numLoaded);

	private:
		std::vector<SpriteObject*> backgroundObjects;
		std::vector<SpriteObject*> parallaxObjects;
		std::vector<SpriteObject*> characterObjects;
		std::vector<SpriteObject*> readableObjects;
		std::vector<Button*> characterButtons;

		Button* leftButton;
		Button* rightButton;

		SpriteObject* loadingBar;

		SpriteObject* loadingLeft;
		SpriteObject* loadingRight;

		SpriteObject* currentBackground;
		SpriteObject* currentCharacter;
		SpriteObject* currentParallax;
		SpriteObject* currentReadable;

		SpriteObject* previousBackground;
		SpriteObject* previousCharacter;
		SpriteObject* previousParallax;

		SpriteObject* glass;

		sf::SoundBuffer* buttonClickBuffer;
		sf::Sound* buttonClick;

		int index = -1;
		sf::Music* music;

		float value = 100;

		int numLoaded = 0;

		bool fadingOut = false;
		bool fadingIn = false;
		bool fadeBetween = false;

		bool fadeInRead = false;
		bool reading = false;
		bool fadeOutRead = false;
	};
}

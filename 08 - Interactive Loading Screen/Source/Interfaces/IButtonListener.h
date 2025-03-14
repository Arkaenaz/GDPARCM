#pragma once

namespace IET
{
	class Button;
	class IButtonListener
	{
    public:
        virtual ~IButtonListener() {}

    public:
        virtual void onClick(Button* pButton) = 0;
        virtual void onHover(Button* pButton) = 0;
        virtual void onRelease(Button* pButton) = 0;
        virtual void reset(Button* pButton) = 0;
	};
}
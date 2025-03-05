#pragma once
#include "IETThread.h"

namespace IET {
	class HelloWorldThread : public IETThread

	{
	public:
		explicit HelloWorldThread(int id);
		~HelloWorldThread() override;

	private:
		void run() override;

		int id = 0;
	};
}
#pragma once

#include "Threading/IETThread.h"

namespace IET
{
	class IExecutionEvent;
	class StreamAssetLoader : public IETThread
	{
	public:
		StreamAssetLoader(String path, IExecutionEvent* executionEvent);
		~StreamAssetLoader();

	private:
		void run() override;

		String path;
		IExecutionEvent* execEvent;
	};
}

#pragma once

#include "Interfaces/IWorkerAction.h"
#include "Threading/IETThread.h"

namespace IET
{
	class IExecutionEvent;
	class StreamAssetLoader : public IWorkerAction
	{
	public:
		StreamAssetLoader(String path, IExecutionEvent* executionEvent);
		~StreamAssetLoader();

	private:
		void onStartTask() override;

		String path;
		IExecutionEvent* execEvent;
	};
}

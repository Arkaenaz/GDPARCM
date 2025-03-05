#pragma once

#include "Interfaces/IWorkerAction.h"

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

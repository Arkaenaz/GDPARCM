#pragma once

#include "Threading/IETThread.h"

namespace IET
{
	class IWorkerAction;
	class IFinishedTask;
	class PoolWorkerThread : public IETThread
	{
	public:
		PoolWorkerThread(int id, IFinishedTask* finishedTask);
		~PoolWorkerThread();

		int getThreadID();
		void assignTask(IWorkerAction* action);

	private:
		void run() override;

		int id = 0;
		IWorkerAction* action;
		IFinishedTask* finishedTask;
	};
}


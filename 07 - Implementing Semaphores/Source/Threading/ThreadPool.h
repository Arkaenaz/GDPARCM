#pragma once

#include "Threading/IETThread.h"

namespace IET {
	class PoolWorkerThread;
	class IWorkerAction;
	class IFinishedTask
	{
	public:
		virtual void onFinished(int threadID) = 0;
	};

	class ThreadPool : public IETThread, public IFinishedTask
	{
	private:
		typedef std::queue<PoolWorkerThread*> ThreadList;
		typedef std::unordered_map<int, PoolWorkerThread*> ActiveThreadMap;
		typedef std::queue<IWorkerAction*> ActionList;

	public:
		ThreadPool(String name, int numWorkers);
		~ThreadPool() override;

		void startScheduler();
		void stopScheduler();
		void scheduleTask(IWorkerAction* action);

	private:
		void run() override;
		void onFinished(int threadID) override;

		String name;
		bool running = false;
		int numWorkers = 0;
		ActiveThreadMap activeThreads;
		ThreadList inactiveThreads;
		ActionList pendingActions;
	};
}


#include "pch.h"
#include "PoolWorkerThread.h"

#include "ThreadPool.h"
#include "Interfaces/IWorkerAction.h"

namespace IET
{
	PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask)
		: id(id), finishedTask(finishedTask)
	{
	}

	PoolWorkerThread::~PoolWorkerThread()
	{
	}

	int PoolWorkerThread::getThreadID()
	{
		return this->id;
	}

	void PoolWorkerThread::assignTask(IWorkerAction* action)
	{
		this->action = action;
	}

	void PoolWorkerThread::run()
	{
		this->action->onStartTask();
		this->finishedTask->onFinished(this->id);
	}
}

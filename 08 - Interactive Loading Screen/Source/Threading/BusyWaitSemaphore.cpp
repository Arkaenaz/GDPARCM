#include "pch.h"
#include "BusyWaitSemaphore.h"

#include "Threading/IETThread.h"

namespace IET
{
	BusyWaitSemaphore::BusyWaitSemaphore(int available, int limit)
	{
		this->permits = available;
		this->maxPermits = limit;
		this->guard = new Mutex();
	}

	BusyWaitSemaphore::BusyWaitSemaphore(int limit)
	{
		this->maxPermits = limit;
		this->permits = this->maxPermits;
		this->guard = new Mutex();
	}

	void BusyWaitSemaphore::acquire()
	{
		this->guard->lock();
		if (this->permits > 0)
		{
			this->permits--;
			this->guard->unlock();
		}
		else
		{
			this->guard->unlock();
			this->wait();
			this->acquire();
			//this->permits--;
		}
	}

	void BusyWaitSemaphore::release()
	{
		this->guard->lock();
		if (this->permits < this->maxPermits)
		{
			this->permits++;
		}
		this->guard->unlock();
	}

	void BusyWaitSemaphore::wait() const
	{
		while (this->permits == 0)
		{
			IETThread::sleep(1);
		}
	}
}

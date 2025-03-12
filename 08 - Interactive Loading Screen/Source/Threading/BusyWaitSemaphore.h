#pragma once

namespace IET
{
	//semaphore through busy waiting
	class BusyWaitSemaphore
	{
	public:
		BusyWaitSemaphore(int available, int limit);
		BusyWaitSemaphore(int limit);
		~BusyWaitSemaphore() = default;

		// should b atomic
		void acquire();
		void release();
	
	private:
		Mutex* guard;
		int permits = 0;
		int maxPermits = 0;
	
		void wait() const; // sleeps the thread and awakes when permits are enough
	};
}
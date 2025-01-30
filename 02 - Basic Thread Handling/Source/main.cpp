#include "pch.h"

#include "IETThread.h"
#include "MyThread.h"

void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void testFunc(int x)
{
	//sleep(3000);
	
	/*while (x < 100)
	{
		x++;
		std::cout << "Hello " << x << "\n";
	}*/
}

int main()
{
    std::cout << "Hello World from thread main!\n";

	constexpr int numThreads = 100;

	MyThread threads[numThreads];

	for (int i = 0; i < numThreads; i++)
	{
		threads[i] = MyThread(i);
		threads[i].start();
	}
	sleep(10000);

	for (int i = 0; i < numThreads; i++)
	{
		threads[i].dismiss();
	}

	/*
		thread.join()	: Main thread waits for completion of the thread before continuing
							- Not persistent
							- Not advanced sync mechanisms
							- Useful if you want data that is really needed
		thread.detach()	: Allows independence of execution from the main thread
							- No rendezvous point
							- Useful for persistent background threads
							- More control over synchronizing data
	*/

	
	/*int x = 0;
	while (x < 100)
	{
		x++;
		std::cout << "Hi " << x << "\n";
	}*/
	std::cout << "Bye World! from Thread main.\n";
	
}
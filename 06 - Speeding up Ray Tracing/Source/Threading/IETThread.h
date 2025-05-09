#pragma once
#include <iostream>
#include <thread>

/// <summary>
/// Representation of a Java/C# like thread class. The behavior must be inherited by a class that needs to be threaded.
/// By: NeilDG
/// </summary>
class IETThread
{
public:
	IETThread();
	virtual ~IETThread();

	void start();
	static void sleep(int ms);
	
protected:
	virtual void run() = 0;
};


#pragma once

#include "IETThread.h"

class MyThread : public IETThread
{
public:
	MyThread() = default;
	explicit MyThread(int id);
	//~MyThread() override;

	void dismiss();

protected:
	void run() override;

private:
	int id;

	bool running;
};


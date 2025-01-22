#include "pch.h"
#include "MyThread.h"

MyThread::MyThread(int id)
{
	this->id = id;
}

void MyThread::run()
{
	this->running = true;
	while (this->running) {
		std::cout << "Hello World from thread : " << this->id << "\n";
		this->sleep(1000);
	}
}

void MyThread::dismiss()
{
	this->running = false;
}

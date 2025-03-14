#pragma once

/// <summary>
/// Representation of a Java/C# like thread class. The behavior must be inherited by a class that needs to be threaded.
/// By: NeilDG
/// </summary>
namespace IET {
	class IETThread
	{
	public:
		IETThread() = default;
		virtual ~IETThread() = default;

		IETThread(const IETThread&) = default;
		IETThread(IETThread&&) = default;
		IETThread& operator=(const IETThread&) = default;
		IETThread& operator=(IETThread&&) = default;

		void start(); //schedules thread execution
		static void sleep(int ms);

	protected:
		virtual void run() = 0;
	};
}
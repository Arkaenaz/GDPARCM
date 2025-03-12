#pragma once

namespace IET
{
	class IWorkerAction
	{
	public:
		virtual void onStartTask() = 0;
	};
}
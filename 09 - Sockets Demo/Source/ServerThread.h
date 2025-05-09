#pragma once
#include <winsock2.h>

#include "IETThread.h"
class ServerThread :    public IETThread
{
public:
	ServerThread();
	~ServerThread() = default;

	void serverStart(); //calling this directly is a non-threading call.

	void sendMessage(std::string msg);

protected:
	void run() override;

private:
	SOCKET clientSocket = INVALID_SOCKET;
	int iResult = 99999;

	bool hasPendingMsg = false;
	std::string msgToSend;
};


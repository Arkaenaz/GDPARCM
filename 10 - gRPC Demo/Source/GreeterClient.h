#pragma once
#include <string>
#include "helloworld.grpc.pb.h"

#include "IETThread.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class GreeterClient : public IETThread
{
public:
	GreeterClient(std::shared_ptr<grpc::ChannelInterface> channel, std::vector<std::string> users);
	std::string SayHello(const std::string& user);
	std::string SayHelloAgain(const std::string& user);

	void runClient();

	void run() override;

private:
	std::unique_ptr<Greeter::Stub> stub_;
	std::vector<std::string> users_;
};


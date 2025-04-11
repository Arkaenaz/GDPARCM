#include "GreeterClient.h"
#include <grpcpp/create_channel.h>

GreeterClient::GreeterClient(std::shared_ptr<grpc::ChannelInterface> channel, std::vector<std::string> users)
{
    this->stub_ = Greeter::NewStub(channel);
    this->users_ = users;
}


std::string GreeterClient::SayHello(const std::string& user)
{
    // Follows the same pattern as SayHello.
    HelloRequest request;
    request.set_name(user);
    HelloReply reply;
    grpc::ClientContext context;

    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(2000);
    context.set_deadline(deadline);

    std::cout << "Sending " << user << " to server." << std::endl;
    // Here we can use the stub's newly available method we just added.
    grpc::Status status = stub_->SayHello(&context, request, &reply);
    if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        return "RPC failed";
    }
}

std::string GreeterClient::SayHelloAgain(const std::string& user)
{
    // Follows the same pattern as SayHello.
    HelloRequest request;
    request.set_name(user);
    HelloReply reply;
    grpc::ClientContext context;

    std::cout << "Sending " << user << " to server." << std::endl;
    // Here we can use the stub's newly available method we just added.
    grpc::Status status = stub_->SayHelloAgain(&context, request, &reply);
    if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        return "RPC failed";
    }
}

void GreeterClient::runClient()
{
    //GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    //std::string user("GDPARCM Student");
    while (true)
    {
        for (std::string user : users_) {
            std::string reply = SayHello(user);
            std::cout << "Greeter received: " << reply << std::endl;

            reply = SayHelloAgain(user);
            std::cout << "Greeter received: " << reply << std::endl;
        }
    }
}

void GreeterClient::run()
{
    runClient();
}

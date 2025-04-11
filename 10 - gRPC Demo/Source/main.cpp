// GDPARCM_HO8 - gRPC Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <grpcpp/create_channel.h>

#include "GreeterServer.h"
#include "GreeterClient.h"

int main()
{
    //run the server
    GreeterServer server;
    server.start();

    //wait for server to startup
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //run the client
    GreeterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()), std::vector<std::string>({"GDPARCM Student"
}));
    client.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

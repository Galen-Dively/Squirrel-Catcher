#include "../headers/client.h"

Client::Client()
{

    test_entity_info.x = 50;
    test_entity_info.y = 50;
    test_entity_info.id = 50;

    sock = 0;
    data_to_send = test_entity_info;
    data_ptr = &data_to_send;


    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Could not connect to server";
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "192.168.41.129", &server_address.sin_addr) <= 0)
    {
        std::cout << "Invalid Address / Address not supported";
    }

    std::cout << "Trying to connect\n";

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        std::cout << "Connection failed. Error: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected\n";

}

void Client::establish()
{
    int data;
    int bytesReceived = recv(sock, &data, sizeof(data), 0);
    if (bytesReceived > 0) {
        id = data;  // Correctly assign the ID received
        std::cout << "Client ID received: " << id << std::endl;
    } 
    else if (bytesReceived == 0) {
        std::cout << "Server closed the connection." << std::endl;
        close(sock);  // Properly close the socket
    } 
    else {
        std::cout << "Failed to receive ID from server. Error: " << strerror(errno) << std::endl;
    }
}


void Client::sendPlayerInfo(const struct entity_info p)
{
    std::cout << "Sending " << p.x <<  " " << p.y << " To Server" << std::endl;
    send(sock, &p, sizeof(p), 0);
}

struct entity_info Client::recievePlayer()
{
    struct entity_info recv_data;
    int valread = recv(sock, &recv_data, sizeof(recv_data), 0);
    if (valread > 0)
    {
        std::cout << "Data received from server!" << recv_data.y << " "<< recv_data.x << std::endl;
    }
    else if (valread == 0)
    {
        std::cout << "Connection closed by the server" << std::endl;
    }
    else
    {
        std::cout << "Failed to receive data" << std::endl;
    }
    return recv_data;
}

int Client::getPlayerID()
{
    return id;
}
#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "../headers/entityinfo.h"
#include <thread>


#define PORT 4444


class Client
{

    public:

    Client();
    int id;
    int sock;
    struct sockaddr_in server_address;
    struct entity_info data_to_send;
    struct entity_info* data_ptr;
    struct entity_info test_entity_info;
    void establish();
    void sendPlayerInfo(const struct entity_info p);
    struct entity_info recievePlayer();
    void loop();
    int getPlayerID();


    private:
};
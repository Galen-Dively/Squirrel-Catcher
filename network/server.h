#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

#define PORT 4444
#define LOG "[LOG]"
#define PLAYER_ONE_ID 1
#define PLAYER_TWO_ID 2

struct entity_info
{
    int id;
    int x;
    int y;
};

class Server
{
public:
    Server();
    void createSocket();
    void start();
    void connection();
    void end();
    void sendPlayerInfo(int id, const struct entity_info &p);
    struct entity_info receivePlayerInfo(int id, struct entity_info &p);
    void parseID(struct entity_info p);

private:
    int server_fd;
    struct sockaddr_in address;
    int addrlen;
    std::vector<int> connections;
    int connections_amt;
};

void runServer(Server &s);

#endif // SERVER_H

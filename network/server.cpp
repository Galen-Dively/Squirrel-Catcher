#include "server.h"
#include <thread>
#include <iostream>
#include <errno.h>
#include <sys/select.h>  // For fd_set, FD_ZERO, FD_SET, FD_ISSET, select()
#include <sys/time.h>    // For struct timeval
#include <cstring>       // For strerror()
#include <unistd.h>      // For close()


Server::Server() : addrlen(sizeof(address)), connections_amt(0)
{
    // Initialize server_fd and other members if needed
}

void Server::createSocket()
{
    // Create the socket descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("[EXIT] Socket Failed");
        exit(EXIT_FAILURE);
    }
}

void Server::start()
{
    fcntl(server_fd, F_SETFL, O_NONBLOCK); // Set the socket to non-blocking mode

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) 
    {
        perror("[EXIT] Socket failed to Bind");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) 
    {
        perror("[EXIT] Server failed to listen");
        exit(EXIT_FAILURE);
    }
}

void Server::connection()
{
    fd_set readfds;  // Set of socket descriptors
    int max_sd;      // Max descriptor number

    while (true) 
    {
        // Clear the set
        FD_ZERO(&readfds);

        // Add the server socket to the set
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        // Add client sockets to the set
        for (int id : connections) 
        {
            FD_SET(id, &readfds);
            if (id > max_sd) 
            {
                max_sd = id;
            }
        }

        // Set the timeout to 1 second (or adjust as needed)
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Wait for activity on one of the sockets (server socket or client sockets)
        int activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR) 
        {
            // std::cerr << "[ERROR] select error: " << strerror(errno) << std::endl;
            continue;
        }

        // Check if there is an incoming connection on the server socket
        if (FD_ISSET(server_fd, &readfds)) 
        {
            int connectionID = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            if (connectionID >= 0) 
            {
                connections.push_back(connectionID);
                connections_amt += 1;
                std::cout << "Connection established with client ID: " << connections_amt << std::endl;

                // Send the player ID to the client
                send(connectionID, &connections_amt, sizeof(connections_amt), 0);
            } 
            else if (errno != EWOULDBLOCK) 
            {
                perror("[INFO] Accept failed");
            }
        }

        // Handle I/O on connected clients
        for (int i = 0; i < connections.size(); ++i) 
        {
            int id = connections[i];
            std::cout << id << std::endl;
            if (FD_ISSET(id, &readfds)) 
            {
                struct entity_info p;
                std::cout << p.x << " " << p.y << " " << p.id << " " << p.connection;
                receivePlayerInfo(id, p);
                parseID(p);
                std::cout << "[LOG] Client " << p.id << "Sent \n";
            }
        }
    }
}


void Server::parseID(struct entity_info p)
{
    // Parses ID and send info to the other player
    if (p.id == PLAYER_ONE_ID) 
    {
        if (connections.size() > 1)
            sendPlayerInfo(connections[1], p);  // Send to player 2
    } 
    else if (p.id == PLAYER_TWO_ID) 
    {
        sendPlayerInfo(connections[0], p);  // Send to player 1
    }
}


void Server::sendPlayerInfo(int id, const struct entity_info &p)
{
    send(id, &p, sizeof(p), 0);
}

struct entity_info Server::receivePlayerInfo(int id, struct entity_info &p)
{
    int valread = read(id, &p, sizeof(p));
    if (valread > 0) 
    {
        std::cout << "[INFO] Client " << id << " sent data" << std::endl;
    } 
    else if (valread == 0) 
    {
        close(id);
        std::cout << "[INFO] Client " << id << " disconnected." << std::endl;
        // Remove client from connections vector here if needed
    }
    return p;
}

void Server::end()
{
    for (int id : connections) 
    {
        close(id);
    }
    close(server_fd);
    std::cout << "[INFO] Server shut down." << std::endl;
}


void runServer(Server &s)
{
    s.createSocket();
    s.start();
    s.connection();
}

int main()
{
    Server s;
    runServer(s);

    return 0;
}

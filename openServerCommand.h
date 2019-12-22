//
// Created by yakir on 12/22/19.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

class openServerCommand {
private:

public:
    openServerCommand();
    openServerCommand(int portNum);
    ~openServerCommand();
    int initServer(int socketfd, sockaddr_in address);


};


#endif //EX3_OPENSERVERCOMMAND_H

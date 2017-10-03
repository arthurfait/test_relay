#include "client_application.h"
#include <signal.h>
#include <iostream>

ClientApplication::ClientApplication(int argc, char ** argv)
    : ApplicationBase(argc, argv)
{
}

ClientApplication::~ClientApplication()
{
}

int ClientApplication::mainLoop()
{
    FileReader fileReader("")
    while (isRun()) {
        Buffer buff;
        fileReader.read(buff);
    }

    std::cout << "apploop exiting";
    std::cout.flush();
    return 0;
}

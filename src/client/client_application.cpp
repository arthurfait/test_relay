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

    while (isRun()) {
//         ThreadImpl::sleep(1000);
    }

    std::cout << "apploop exiting";
    std::cout.flush();
    return 0;
}

#include "server_application.h"
#include <signal.h>
#include <iostream>

ServerApplication::ServerApplication(int argc, char ** argv)
    : ApplicationBase(argc, argv)
{
}

ServerApplication::~ServerApplication()
{
}

int ServerApplication::mainLoop()
{
    reciverSvc.StartThread();
    while (isRun()) {
        ThreadImpl::sleep(1000);
    }
    reciverSvc.Join();
    std::cout << "apploop exiting";
    std::cout.flush();
    return 0;
}

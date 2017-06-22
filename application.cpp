#include "application.h"
#include "application_priv.h"

#include <signal.h>
#include <iostream>

bool AppData::g_run = true;

void AppData::shandler(int signum)
{
    g_run = false;
}

Application::Application(int argc, char ** argv)
{
    std::cout.sync_with_stdio(false);
    data_.reset(new AppData);
    signal(SIGTERM, AppData::shandler);
    signal(SIGPIPE, AppData::shandler);
    signal(SIGQUIT, AppData::shandler);
    signal(SIGINT, AppData::shandler);
}

Application::~Application()
{
    signal(SIGTERM, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}

int Application::run()
{
    std::cout << "App loop started\n";
    std::cout.flush();
    data_->reciverSvc.StartThread();
    while (AppData::g_run) {
        ThreadImpl::sleep(1000);
    }
    std::cout << "apploop stopped";
    std::cout.flush();

    data_->reciverSvc.Join();
    std::cout << "apploop exiting";
    std::cout.flush();
    return 0;
}

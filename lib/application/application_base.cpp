#include "application_base.h"
#include "application_base_priv.h"

#include <signal.h>
#include <iostream>


ApplicationBase::ApplicationBase(int argc, char ** argv)
{
    std::cout.sync_with_stdio(false);
    data_.reset(new AppData);
    signal(SIGTERM, AppData::shandler);
    signal(SIGPIPE, AppData::shandler);
    signal(SIGQUIT, AppData::shandler);
    signal(SIGINT, AppData::shandler);
}

ApplicationBase::~ApplicationBase()
{
    signal(SIGTERM, SIG_DFL);
    signal(SIGPIPE, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}

int ApplicationBase::run()
{
    std::cout << "App loop started\n";
    std::cout.flush();
    int r = mainLoop();
    std::cout << "apploop stopped";
    std::cout.flush();
    return r;
}

bool ApplicationBase::isRun()
{
    return data_->g_run;
}

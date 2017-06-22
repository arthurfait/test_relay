#ifndef APPLICATION_PRIV_H
#define APPLICATION_PRIV_H

#include "test_thread_recive.h"

struct AppData
{
    TestThreadSend reciverSvc;
    static bool g_run;
    static void shandler(int signum);
};

#endif // APPLICATION_PRIV_H

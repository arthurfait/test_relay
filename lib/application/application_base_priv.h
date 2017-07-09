#ifndef APPLICATION_BASE_PRIV_H
#define APPLICATION_BASE_PRIV_H

#include "application_base.h"

struct ApplicationBase::AppData
{
    static bool g_run;
    static void shandler(int signum);
};

#endif // APPLICATION_BASE_PRIV_H

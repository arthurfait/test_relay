#include "application_base_priv.h"

bool ApplicationBase::AppData::g_run = true;

void ApplicationBase::AppData::shandler(int signum)
{
    g_run = false;
}

/*****************************************************************************/
/*!
 * @company    Luxoft
 * @file       thread.cpp
 * @author     Alexey Volokitin
 * @version    1.0
 * @brief
 * @date       Oct 12, 2016
 * @copyright  Luxoft 2016
 *             All rights reserved.
 */
/*****************************************************************************/


#include "thread.h"

void ThreadImpl::sleep(unsigned long millisec)
{
    usleep(millisec*1000);
}

ThreadImpl::ThreadImpl()
    : m_handle(0)
    , m_state(THREAD_STOPPED)
{
}

ThreadImpl::~ThreadImpl()
{
    if (m_handle)
    {
        pthread_detach(m_handle);
        m_handle = 0;
    }
}

bool ThreadImpl::StartThread()
{
    {
        CSLocker locker(&m_cs);
        if (m_state != THREAD_STOPPED) {
            return false;
        }
        m_state = THREAD_START_PENDING;
        m_startSemaphore.Release();
        m_stopSemaphore.Release();
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int re = pthread_create(&m_handle, &attr, ThreadProc, this);
    pthread_attr_destroy(&attr);
    if (re != 0)
        return false;

    while (!WaitRun(100)) {}
    return true;
}

void ThreadImpl::Join()
{
    if (!m_handle || m_state == THREAD_STOPPED) {
        return;
    } else if (m_state == THREAD_START_PENDING) {
        while(!WaitRun(100)){}
    }

    StopThread();

    Stop();

    while (!WaitStop(100)) {}

    pthread_join(m_handle, 0);
    m_handle = 0;
}

void* ThreadImpl::ThreadProc(void* arg)
{
    ThreadImpl* thread = (ThreadImpl*)arg;
    {
        CSLocker locker(&thread->m_cs);
        thread->m_state = THREAD_RUNNING;
        thread->m_startSemaphore.Set();
    }

    thread->OnStart();
    thread->ThreadFunc();
    thread->OnStop();

    {
        CSLocker locker(&thread->m_cs);
        thread->m_state = THREAD_STOPPED;
        thread->m_stopSemaphore.Set();
    }

    return 0;
}

bool ThreadImpl::IsStopped() const
{
    return m_state == THREAD_STOPPED;
}

bool ThreadImpl::IsStop()
{
    return m_state == THREAD_STOP_PENDING;
}

bool ThreadImpl::WaitStop(int timeout)
{
    if (!IsStopped())
    {
        return m_stopSemaphore.Wait(timeout) == Semaphore::SUCCESS;
    }
    return true;
}

bool ThreadImpl::WaitRun(int timeout)
{
    if (!IsRunning())
    {
        return m_startSemaphore.Wait(timeout) == Semaphore::SUCCESS;
    }
    return true;
}

bool ThreadImpl::IsRunning()
{
    return m_state == THREAD_RUNNING;
}


void ThreadImpl::StopThread()
{
    CSLocker locker(&m_cs);
    if (m_state != THREAD_STOPPED)
    {
        m_state = THREAD_STOP_PENDING;
    }
}

/*****************************************************************************/
/*!
 * @company    Luxoft
 * @file       thread.h
 * @author     Alexey Volokitin
 * @version    1.0
 * @brief
 * @date       Oct 12, 2016
 * @copyright  Luxoft 2016
 *             All rights reserved.
 */
/*****************************************************************************/


#ifndef THREAD_H
#define THREAD_H

#include "critical_section.h"
#include "semaphore.hpp"

#include <pthread.h>
#include <unistd.h>

class ThreadImpl
{
public:
    enum ThreadState
    {
        THREAD_STOPPED = 0,
        THREAD_RUNNING,
        THREAD_STOP_PENDING,
        THREAD_START_PENDING
    };

    ThreadImpl();
    virtual ~ThreadImpl();

public:
    /**
     * Start thread execution
     * @return true on ok
     */
    bool StartThread();

    /**
     * Stop thread execution
     */
    void StopThread();

    /**
     * Request stop execution and wait for thread finish
     */
    void Join();

    /**
     * check if thread is running
     * @return true on ok
     */
    bool IsRunning();

    /**
     * check if thread is stopped
     */
    bool IsStopped() const;

    /**
     * check if thread is about to stop
     * @return true on ok
     */
    bool IsStop();

    /**
     * Wait for thread stop
     * @param timeout time in ms to wait
     * @return true on ok
     */
    bool WaitStop(int timeout);

    /**
     * Wait for thread run
     * @param timeout dd
     * @return status
     */
    bool WaitRun(int timeout);

    /**
     * sleep for n ms
     * @param millisec timeout in milisceconds
     */
    static void sleep(unsigned long millisec);

public:
    static void* ThreadProc(void* arg);

    /**
     * tread function it self
     */
    virtual void ThreadFunc() = 0;

    /**
     * called after exit from thread function
     */
    virtual void OnStop() {};

    /**
     * called before entering start function
     */
    virtual void OnStart() {};

    /**
     * called in Join operation
     */
    virtual void Stop() {};

private:
    typedef pthread_t ThreadHandle;
    ThreadHandle m_handle;
    Semaphore m_startSemaphore;
    Semaphore m_stopSemaphore;
    ThreadState m_state;
    CriticalSection m_cs;
};

#endif/*THREAD_H*/

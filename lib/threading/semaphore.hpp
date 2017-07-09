/*****************************************************************************/
/*!
 * @company    Luxoft
 * @file       semaphore.hpp
 * @author     Alexey Volokitin
 * @version    1.0
 * @brief
 * @date       Oct 12, 2016
 * @copyright  Luxoft 2016
 *             All rights reserved.
 */
/*****************************************************************************/


#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#define INFINITE    -1

class Semaphore
{
public:
    enum WaitStatus
    {
        TIMEOUT,
        FAILED,
        SUCCESS
    };
public:
    Semaphore(int initial = 0, int count = 1)
    {
        sem_init(&m_semafor, 0, initial);
    }

    ~Semaphore()
    {
        sem_destroy(&m_semafor);
    }

    void Set()
    {
        sem_post(&m_semafor);
    }

    void Release()
    {
        sem_trywait(&m_semafor);
    }

    WaitStatus Wait(int timeout)
    {
        int ret;
        if(timeout == INFINITE)
        {
            ret = sem_wait(&m_semafor);
        }
        else
        {
            struct timespec tm = {timeout, timeout*1000000};
            ret = sem_timedwait(&m_semafor, &tm);
        }
        if(ret && errno == ETIMEDOUT)
        {
            return TIMEOUT;
        }
        else if(!ret)
        {
            sem_post(&m_semafor);
            return SUCCESS;
        }
        return FAILED;
    }

    bool IsSet()
    {
        int ret = sem_trywait(&m_semafor);
        if(ret == 0)
        {
            sem_post(&m_semafor);
            return true;
        }
        return false;
    }

private:
    sem_t m_semafor;
};

#endif/*SEMAFOR_H*/

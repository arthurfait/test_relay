/*****************************************************************************/
/*!
 * @company    Luxoft
 * @file       critical_section.h
 * @author     Alexey Volokitin
 * @version    1.0
 * @brief
 * @date       Oct 12, 2016
 * @copyright  Luxoft 2016
 *             All rights reserved.
 */
/*****************************************************************************/


#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include <pthread.h>
#include <sys/types.h>

class CriticalSection
{
public:
	CriticalSection()
    {
        pthread_mutex_init(&m_cs, 0);
        m_threadlock = 0;
    }
	~CriticalSection()
    {
        pthread_mutex_destroy (&m_cs);
        m_threadlock = 0;
    }

	void Enter()
    {
        if(m_threadlock != pthread_self())
        {
            pthread_mutex_lock (&m_cs);
            m_threadlock = pthread_self();
        }
        else
            m_cs.__data.__count++;
    }

	void Leave()
    {
        if(m_threadlock == pthread_self() &&
           m_cs.__data.__count == 0)
        {
            m_threadlock = 0;
            pthread_mutex_unlock(&m_cs);
        }
        else
            m_cs.__data.__count--;
    }
private:
	pthread_mutex_t m_cs;
	pthread_t m_threadlock;
};

class CSLocker
{
public:
	CSLocker(CriticalSection* cs)
    : m_cs(cs)
    {
        m_cs->Enter();
    }

	~CSLocker()
    {
        m_cs->Leave();
    }
private:
	CriticalSection* m_cs;
};

#endif/*CRITICAL_SECTION_H*/

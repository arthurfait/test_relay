#ifndef TEST_THREAD_RECIVE_H
#define TEST_THREAD_RECIVE_H

#include "thread.h"
#include "tcp_socket.h"

class TestThreadSend: public ThreadImpl
{
    RelaySocket sock_;
public:
    TestThreadSend ()
    : sock_(RelaySocket::IPV4)
    {

    }
    virtual void ThreadFunc();
};

#endif // TEST_THREAD_RECIVE_H

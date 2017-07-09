#ifndef SERVER_APPLICATION_H_
#define SERVER_APPLICATION_H_

#include <memory>
#include <application_base.h>
#include "test_thread_recive.h"

/**
 * @brief ServerApplication main class
 */
class ServerApplication: public ApplicationBase {
public:
    ServerApplication(int argc, char **argv);
    ~ServerApplication();
protected:
    virtual int mainLoop() override;
private:
    DISALLOW_COPY_MOVE_AND_ASSIGN(ServerApplication);
private:
    TestThreadSend reciverSvc;
};


#endif // SERVER_APPLICATION_H_

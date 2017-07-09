#ifndef CLIENT_APPLICATION_H_
#define CLIENT_APPLICATION_H_

#include <memory>
#include <application_base.h>

/**
 * @brief ClientApplication main class
 */
class ClientApplication: public ApplicationBase {
public:
    ClientApplication(int argc, char **argv);
    ~ClientApplication();
protected:
    virtual int mainLoop() override;
private:
    DISALLOW_COPY_MOVE_AND_ASSIGN(ClientApplication);
private:
};


#endif // CLIENT_APPLICATION_H_

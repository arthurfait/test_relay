#ifndef APPLICATION_BASE_H_
#define APPLICATION_BASE_H_

#include <memory>
#include "common_defines.h"

/**
 * @brief ApplicationBase main class
 */
class ApplicationBase {
public:
    ApplicationBase(int argc, char **argv);
    ~ApplicationBase();

    /**
     * @brief run application mainloop
     * @return exit code for lopp, cna be used as application exit code
     */
    int run();

protected:

    /**
     * @brief shall be overiden ton anble mainLoop
     */
    virtual int mainLoop() = 0;

    bool isRun();

private:
    DISALLOW_COPY_MOVE_AND_ASSIGN(ApplicationBase);

private:
    struct AppData;
    std::unique_ptr<AppData> data_;
};


#endif // APPLICATION_BASE_H_

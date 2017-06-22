#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <memory>
#include "test_thread_recive.h"


struct AppData;

class Application {
public:
    Application(int argc, char **argv);
    ~Application();

    int run();
private:
    Application(const Application& classRef) = delete;
    Application(Application&& classURef) = delete;

    Application& operator=(const Application& classRef) = delete;
    Application& operator=(Application&& classURef) = delete;
private:
    std::unique_ptr<AppData> data_;
};


#endif // APPLICATION_H_

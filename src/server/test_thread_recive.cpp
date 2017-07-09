/**
 * @brief
 */

#include "test_thread_recive.h"
#include <vector>
#include <iostream>

void TestThreadSend::ThreadFunc()
{
    sock_.Bind("localhost", 0);
    sock_.Listen(1);
    std::string myp;
    int selfport = 0;
    sock_.GetIPPort(myp, selfport);
    std::cout<< selfport << "\n";
    std::cout.flush();
    std::string peer_ip = "";
    std::int32_t peer_port = 0;
    sock_.Accept(peer_ip, peer_port);
    std::vector<char> buffer(1024);
    while (IsRunning()) {
        int recived = sock_.Recv(buffer.data(), buffer.size());
        if (recived > 0) {
            std::cout << "recived: " << recived << "\n";
            sock_.Send(buffer.data(), recived);
        } else {
            ThreadImpl::sleep(100);
        }

    }
    std::cout << "Bye!\n";
}

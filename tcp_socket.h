/*****************************************************************************/
/*!
 * @company    Luxoft
 * @file       tcp_socket.h
 * @author     Alexey Volokitin
 * @version    1.0
 * @brief
 * @date       Oct 12, 2016
 * @copyright  Luxoft 2016
 *             All rights reserved.
 */
/*****************************************************************************/


#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <string>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define SD_BOTH SHUT_RDWR

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif /*INVALID_SOCKET*/


#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif /*SOCKET_ERROR*/

#include "critical_section.h"


class RelaySocket
{
public:
    enum IPVersion
    {
        IPV4 = AF_INET,
        IPV6 = AF_INET6
    };

    explicit RelaySocket(IPVersion ipv);
    explicit RelaySocket(int socket);
	virtual ~RelaySocket();

	virtual bool Bind(const std::string& host, int port);
	virtual bool Listen(int limit);
	virtual int Accept(std::string& ip, int& port);
	virtual bool Connect(const std::string& host, int port);
	virtual int32_t Send(const char* data, int len);
	virtual int32_t Recv(char* data, int len);
	virtual void GetIPPort(std::string& ip, int& port);
	virtual bool Close();
    virtual int GetSocket();
    virtual int GetMaxBufferSize();
protected:
    void Initialize();
private:
    int m_socket;
    IPVersion m_ipv;
    CriticalSection m_cs;
};

#endif/*TCP_SOCKET_H*/

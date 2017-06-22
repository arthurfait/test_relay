/*****************************************************************************/
/*!
 * @company    Luxoft
 * @file       tcp_socket.cpp
 * @author     Alexey Volokitin
 * @version    1.0
 * @brief
 * @date       Oct 12, 2016
 * @copyright  Luxoft 2016
 *             All rights reserved.
 */
/*****************************************************************************/

#include "tcp_socket.h"

RelaySocket::RelaySocket(IPVersion ipv)
    : m_ipv(ipv)
{
    Initialize();
}

RelaySocket::RelaySocket(int socket)
    : m_socket(socket)
{
    sockaddr_storage si;
    unsigned int len = sizeof(si);
    getsockname(m_socket, (sockaddr*)&si, &len);
    m_ipv = (IPVersion)si.ss_family;
}

RelaySocket::~RelaySocket()
{
    Close();
}

bool RelaySocket::Bind(const std::string& host, int port)
{
    if (m_socket == INVALID_SOCKET) {
        return false;
    }


    sockaddr_storage si = {0};
    si.ss_family = m_ipv;
    if (host.empty()) {
        if (m_ipv == IPV4) {
            ((sockaddr_in&)si).sin_addr.s_addr = INADDR_ANY;
        } else {
            ((sockaddr_in6&)si).sin6_addr = in6addr_any;
        }
    } else {
        char portstr[10] = {0};
        sprintf(portstr, "%d", port);
        addrinfo hints = {0}, *result;
        hints.ai_family = m_ipv;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        int ret = getaddrinfo(host.c_str(), portstr, &hints, &result);
        if (!ret) {
            for(addrinfo *addr = result; addr != 0; addr = addr->ai_next) {
                if(addr->ai_family == m_ipv) {
                    memcpy(&si, addr->ai_addr, addr->ai_addrlen);
                }
            }
            freeaddrinfo(result);
        }
    }

    return bind(m_socket, (sockaddr*)&si, m_ipv == IPV4 ? sizeof(sockaddr_in) : sizeof(sockaddr_in6)) == 0;
}

bool RelaySocket::Listen(int limit)
{
    if (m_socket == INVALID_SOCKET) {
        return false;
    }
    return listen(m_socket, limit) == 0;
}

int RelaySocket::Accept(std::string& ip, int& port)
{
    if (m_socket == INVALID_SOCKET) {
        return INVALID_SOCKET;
    }

    sockaddr_storage si;
    unsigned int len = sizeof(si);
    int sock = (int)accept(m_socket, (sockaddr*)&si, &len);
    size_t lenaddr = 0;
    void* paddr = 0;
    if (m_ipv == IPV4) {
        paddr = &((sockaddr_in&)si).sin_addr;
        len = INET_ADDRSTRLEN;
        port = ntohs(((sockaddr_in&)si).sin_port);
    } else {
        paddr = &((sockaddr_in6&)si).sin6_addr;
        len = INET6_ADDRSTRLEN;
        port = ntohs(((sockaddr_in6&)si).sin6_port);
    }

    char *ipinput = new char[len];
    inet_ntop(m_ipv, paddr, ipinput, lenaddr);
    ip = ipinput;
    delete []ipinput;
    return sock;
}

bool RelaySocket::Connect(const std::string& host, int port)
{
    if (m_socket == INVALID_SOCKET || host.empty()) {
        return false;
    }

    sockaddr_storage si;
    si.ss_family = m_ipv;
    char portstr[10] = {0};
    sprintf(portstr, "%d", port);
    addrinfo hints = {0}, *result;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    int ret = getaddrinfo(host.c_str(), portstr, &hints, &result);
    if (!ret) {
        for (addrinfo *addr = result; addr != 0; addr = addr->ai_next) {
            if(addr->ai_family == m_ipv) {
                memcpy(&si, addr->ai_addr, addr->ai_addrlen);
            }
        }
        freeaddrinfo(result);
        //TODO: if ip version 6 and host ip version 4, convert ip4 to ip6
    }

    int r = connect(m_socket, (sockaddr*)&si, (m_ipv == IPV4) ? sizeof(sockaddr_in) : sizeof(sockaddr_in6));
    return r == 0;
}

int32_t RelaySocket::Send(const char* data, int len)
{
    if (m_socket == INVALID_SOCKET)
    {
        return -1;
    }

    CSLocker locker(&m_cs);
    int sendlen = len;
    while (sendlen > 0)
    {
        int res = send(m_socket, data + len - sendlen, sendlen, 0);
        if (res <= 0)
        {
            return (len - sendlen);
        }

        sendlen -= res;
    }

    return len;
}

int32_t RelaySocket::Recv(char* data, int len)
{
    if (m_socket == INVALID_SOCKET) {
        return -1;
    }

    int res = recv(m_socket, data, len, 0);
    if (res <= 0) {
        return -2;
    }

    return res;
}

bool RelaySocket::Close()
{
    if (m_socket == INVALID_SOCKET)
    {
        return false;
    }

    shutdown(m_socket, SD_BOTH);
    return close(m_socket) == 0;
}

void RelaySocket::GetIPPort(std::string& ip, int& port)
{
    sockaddr_storage addr = {0};
    unsigned int len = sizeof(addr);
    if (!getsockname(m_socket, (sockaddr*)&addr, &len))
    {
        size_t len = 0;
        void* paddr = 0;
        if (m_ipv == IPV4)
        {
            paddr = &((sockaddr_in&)addr).sin_addr;
            len = INET_ADDRSTRLEN;
            port = ntohs(((sockaddr_in&)addr).sin_port);
        }
        else
        {
            paddr = &((sockaddr_in6&)addr).sin6_addr;
            len = INET6_ADDRSTRLEN;
            port = ntohs(((sockaddr_in6&)addr).sin6_port);
        }

        char *ipinput = new char[len];
        inet_ntop(m_ipv, paddr, ipinput, len);
        ip = ipinput;
        delete[] ipinput;
    }
}

int RelaySocket::GetSocket()
{
    return m_socket;
}

void RelaySocket::Initialize()
{
    m_socket = (int)socket(m_ipv, SOCK_STREAM, IPPROTO_TCP);
    int opt = 0;
    socklen_t len = sizeof(opt);
    getsockopt(m_socket, SOL_SOCKET, IPV6_V6ONLY, (char*)&opt, &len);
}

int RelaySocket::GetMaxBufferSize()
{
    if (m_socket == INVALID_SOCKET)
    {
        return 0;
    }

    int sndsize, rcvsize;
    socklen_t len = sizeof(sndsize);
    if (getsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char*)&sndsize, &len) != 0 ||
        getsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (char*)&rcvsize, &len) != 0)
    {
        return 0;
    }

    return ((sndsize < rcvsize) ? sndsize : rcvsize);
}

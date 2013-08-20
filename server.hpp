
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <dns_packet.hpp>
#include <dinestypes.hpp>

class Server {
    DnsPacket _p;
    uint16_t _port;
    Dines::LogFunc _log;
    std::string _data() const;
public:
    Server(const DnsPacket& p, uint16_t port, Dines::LogFunc log = NULL);
    void setLogger(Dines::LogFunc l);
    void launch();
};

#endif

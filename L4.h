//
// Created by danie on 10/06/2025.
//

#ifndef L4_H
#define L4_H
#include "common.hpp"
#include "packets.hpp"
using std::string;



class L4 : public generic_packet {
protected: string src_port;
    string dst_port;
    string addrs;
    string data;
    string packet;


public:
    virtual bool validate_packet(open_port_vec open_ports,
                                 uint8_t ip[IP_V4_SIZE],
                                 uint8_t mask,
                                 uint8_t mac[MAC_SIZE]);

    virtual bool proccess_packet(open_port_vec &open_ports,
                                 uint8_t ip[IP_V4_SIZE],
                                 uint8_t mask,
                                 memory_dest &dst);
    virtual bool as_string(std::string &packet);
    L4(string packet);

};



#endif //L4_H
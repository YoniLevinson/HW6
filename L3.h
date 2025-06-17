
//
// Created by danie on 16/06/2025.
//

#ifndef L3_H
#define L3_H
#include "L4.h"



class L3 : public L4{
protected: string ip_src;
    string ip_dst;
    int TTL;
    int check_sum;
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
    L3(string packet);
    bool checkSum();
    static int ip_sum(string ip);
};




#endif //L3_H

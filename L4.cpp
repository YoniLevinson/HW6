//
// Created by yonil on 10/06/2025.
//

#include "L4.h"
#include "common.hpp"

L4::L4(string packet) {
    this->packet = packet;
    src_port = generic_packet::extract_between_delimiters(packet, '|', 0, 1);
    dst_port = generic_packet::extract_between_delimiters(packet, '|', 1, 2);
    addrs = generic_packet::extract_between_delimiters(packet, '|', 2, 3);
    data = generic_packet::extract_between_delimiters(packet, '|', 3);
}

bool L4::proccess_packet(open_port_vec &open_ports,
                         uint8_t ip[IP_V4_SIZE],
                         uint8_t mask,
                         memory_dest &dst) {
    if(open_ports.empty()){
        return false;
    }
    for (auto open_port: open_ports) {
        int adr = (stoi(addrs));
        if (std::stoi(src_port) == open_port.src_prt && std::stoi(dst_port) == open_port.dst_prt) {
            for (int i = 0; i < 32; i++) {
                string byte = generic_packet::extract_between_delimiters(data, ' ', i, i + 1);
                char byte_data = (char)(stoi(byte, 0, 16));
                open_port.data[adr + i] = byte_data;
            }
        }
    }
    return true;
}

bool L4::validate_packet(open_port_vec open_ports,
                         uint8_t ip[IP_V4_SIZE],
                         uint8_t mask,
                         uint8_t mac[MAC_SIZE]){
    for (auto open_port: open_ports) {
        if (stoi(src_port) == open_port.src_prt && stoi(dst_port) == open_port.dst_prt) {
            if (stoi(addrs) < 32) {
                return true;
            }
        }
    }
    return false;
}

bool L4::as_string(std::string &packet){
    packet = this->packet;
}
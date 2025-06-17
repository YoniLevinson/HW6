//
// Created by danie on 16/06/2025.
//

#include "L3.h"
int L3 :: ip_sum(string ip) {
    int sum = 0;
    sum += stoi (generic_packet::extract_between_delimiters(ip, '.', 0, 1));
    sum += stoi (generic_packet::extract_between_delimiters(ip, '.', 1, 2));
    sum += stoi (generic_packet::extract_between_delimiters(ip, '.', 2, 3));
    sum += stoi (generic_packet::extract_between_delimiters(ip, '.', 3));
    return sum;
}

bool L3 :: checkSum(){
    int sum = 0;
    sum += ip_sum(ip_src);
    sum += ip_sum(ip_dst);
    sum += TTL;
    int s_p = stoi(src_port);
    sum += (((s_p>>24)&(0x000000ff)) + ((s_p>>16)&(0x000000ff))
            + ((s_p>>8)&(0x000000ff)) + (s_p&(0x000000ff)));
    int d_p = stoi(dst_port);
    sum += (((d_p>>24)&(0x000000ff)) + ((d_p>>16)&(0x000000ff))
            + ((d_p>>8)&(0x000000ff)) + (d_p&(0x000000ff)));
    int address = stoi(addrs);
    sum += address;
    for (int i = 0; i < 32; i++) {
        string byte = generic_packet::extract_between_delimiters(data, ' ', i, i + 1);
        int byte_data = stoi(byte, 0, 16);
        sum += byte_data;
    }
    return (sum == check_sum);
}


L3::L3(string packet):L4(generic_packet::extract_between_delimiters(packet,'|',4)){
    ip_src = generic_packet::extract_between_delimiters(packet, '|', 0, 1);
    ip_dst = generic_packet::extract_between_delimiters(packet, '|', 1, 2);
    TTL = stoi(generic_packet::extract_between_delimiters(packet, '|', 2, 3));
    check_sum = stoi(generic_packet::extract_between_delimiters(packet, '|', 3, 4));
}


bool L3::validate_packet(open_port_vec open_ports,
                         uint8_t ip[IP_V4_SIZE],
                         uint8_t mask,
                         uint8_t mac[MAC_SIZE]){
    if (!(L4::validate_packet(open_ports, ip, mask, mac))) {
        return false;
    }
    if (TTL <= 0) {
        return false;
    }
    return false;
}



bool L3::proccess_packet(open_port_vec &open_ports,
                     uint8_t ip[IP_V4_SIZE],
                     uint8_t mask,
                     memory_dest &dst) {
    return false;
}
bool L3::as_string(std::string &packet) {
    return false;
}
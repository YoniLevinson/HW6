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
int L3 :: sum(){
    int sum = 0;
    sum += ip_sum(ip_src);
    sum += ip_sum(ip_dst);
    sum += TTL;
    int s_p = stoi(l4.get_src_port());
    sum += (((s_p>>24)&(0x000000ff)) + ((s_p>>16)&(0x000000ff))
            + ((s_p>>8)&(0x000000ff)) + (s_p&(0x000000ff)));
    int d_p = stoi(l4.get_dst_port());
    sum += (((d_p>>24)&(0x000000ff)) + ((d_p>>16)&(0x000000ff))
            + ((d_p>>8)&(0x000000ff)) + (d_p&(0x000000ff)));
    int address = stoi(l4.get_addrs());
    sum += address;
    for (int i = 0; i < 32; i++) {
        string byte = generic_packet::extract_between_delimiters(l4.get_data(), ' ', i, i + 1);
        int byte_data = stoi(byte, 0, 16);
        sum += byte_data;
    }
    return sum;
}
bool L3 :: checkSum(){
    int sum = L3::sum();
    return (sum == check_sum);
}


L3::L3(string packet): l4(L4(generic_packet::extract_between_delimiters(packet,'|',4))){
    ip_src = generic_packet::extract_between_delimiters(packet, '|', 0, 1);
    ip_dst = generic_packet::extract_between_delimiters(packet, '|', 1, 2);
    TTL = stoi(generic_packet::extract_between_delimiters(packet, '|', 2, 3));
    check_sum = stoi(generic_packet::extract_between_delimiters(packet, '|', 3, 4));
}


bool L3::validate_packet(open_port_vec open_ports,
                         uint8_t ip[IP_V4_SIZE],
                         uint8_t mask,
                         uint8_t mac[MAC_SIZE]){
    if (!(l4.validate_packet(open_ports, ip, mask, mac))) {
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
    bool src_ip_inLocal_network;
    bool dst_ip_inLocal_network;
    unsigned int src_ip_first_byte = stoi(generic_packet::extract_between_delimiters(ip_src, '.', 0, 1));
    unsigned int src_ip_second_byte = stoi(generic_packet::extract_between_delimiters(ip_src, '.', 1, 2));
    unsigned int src_ip_third_byte = stoi(generic_packet::extract_between_delimiters(ip_src, '.', 2, 3));
    unsigned int src_ip_fourth_byte = stoi(generic_packet::extract_between_delimiters(ip_src, '.', 3, 4));
    unsigned int src_ip_number = (src_ip_first_byte<<24)+(src_ip_second_byte<<16)+(src_ip_third_byte<<8)+src_ip_fourth_byte;
    unsigned int dst_ip_first_byte = stoi(generic_packet::extract_between_delimiters(ip_dst, '.', 0, 1));
    unsigned int dst_ip_second_byte = stoi(generic_packet::extract_between_delimiters(ip_dst, '.', 1, 2));
    unsigned int dst_ip_third_byte = stoi(generic_packet::extract_between_delimiters(ip_dst, '.', 2, 3));
    unsigned int dst_ip_fourth_byte = stoi(generic_packet::extract_between_delimiters(ip_dst, '.', 3, 4));
    unsigned int dst_ip_number = (dst_ip_first_byte<<24)+(dst_ip_second_byte<<16)+(dst_ip_third_byte<<8)+dst_ip_fourth_byte;
    unsigned int masker = (~((2^mask)-1));
    unsigned int local_ip = (ip[0]<<24)+(ip[1]<<16)+(ip[2]<<8)+(ip[3]);
    src_ip_inLocal_network = ((src_ip_number&masker) == (local_ip&masker));
    dst_ip_inLocal_network = ((dst_ip_number&masker) == (local_ip&masker));
    if(!src_ip_inLocal_network && dst_ip_inLocal_network){
        TTL--;
        if(TTL == 0){
            return false;
        }
        int sum = L3::sum();
        check_sum = sum;
        //return here
    }
    if(!dst_ip_inLocal_network && src_ip_inLocal_network){

    }

}
bool L3::as_string(std::string &packet) {
    return false;
}
/**
 * @file main.hpp
 * @brief This C++ file contains the main function of the NIC simulation project.
 */

#include <iostream>
#include <cassert>
#include <fstream>
#include "NIC_sim.hpp"
#include "packets.hpp"

int main(int argc, char *argv[]) {
//    std::string param_file;
//    std::string packet_file;
//
//    assert((argc == 3) && "Expected 2 arguments: <param_file> <packet_file>");
//
//    param_file = argv[1];
//    packet_file = argv[2];
//
//    /* Updating simulation parameters. */
//    nic_sim simulation(param_file);
//
//    /* Proccess all packets. */
//    simulation.nic_flow(packet_file);
//
//    /* Print all memory spaces. */
//    simulation.nic_print_results();
 //   L4 l4("2000|2500|0|0D 0A 14 34 65 3F");
//    int sum = 0;
//    string A = "DD";
//
//    int a = (stoi(A,nullptr,16));
//    std::cout << '\n' << a;
//
//    int sum = 0;
//    string A = "2000";
//    int a = stoi(A);
//    int int1 = a>>8;
//    int int2 = (a&0xff);
//    sum = sum + int1 + int2;
//    std::cout << '\n' << int2 << '\n';
//    return std::stoi("DD", 0, 16);
    int sum = 0;
    int s_p = std::stoi("1800000");
    sum += (((s_p>>24)&(0x000000ff)) + ((s_p>>16)&(0x000000ff)) + ((s_p>>8)&(0x000000ff)) + (s_p&(0x000000ff)));
    std::cout << sum << '\n';
    return 0;
}
/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:20:39
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-04 23:52:36
 * @FilePath: /TransportCatalogue/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <string>

#include "input_reader.h"
#include "stat_reader.h"

#include "test_transport_catalogue.h"

int main() {
    transport_catalogue::detail::test::TestTranspotCatalogue();

    transport_catalogue::TransportCatalogue catalogue;

    int base_request_count;
    std::cin >> base_request_count >> std::ws;

    {
        transport_catalogue::detail::InputReader reader;
        for (int i = 0; i < base_request_count; ++i) {
            std::string line;
            std::getline(std::cin, line);
            reader.ParseLine(line);
        }
        reader.ApplyCommands(catalogue);
    }

    int stat_request_count;
    std::cin >> stat_request_count >> std::ws;
    for (int i = 0; i < stat_request_count; ++i) {
        std::string line;
        std::getline(std::cin, line);
        transport_catalogue::detail::ParseAndPrintStat(catalogue, line, std::cout);
    }
}
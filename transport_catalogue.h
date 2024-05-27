/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:22:46
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-26 23:12:14
 * @FilePath: /TransportCatalogue/transport_catalogue.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <deque>
#include "geo.h"
#include <string>
#include <unordered_map>
#include <vector>
struct Stop{
    std::string name;
    Coordinates coordinates;
};
struct Bus{
    std::string name;
    std::vector<Stop*> stops;
};

class TransportCatalogue {
public:
    static constexpr std::string_view stop_cmd = {"Stop"};
    static constexpr std::string_view bus_cmd = {"Bus"};

    void AddStop(Stop&& in_stop);
    void AddBus(Bus&& in_bus);

    Stop* FindStop(std::string_view in_stop_name);
    Bus*  FindBus(std::string_view in_bus_name);
    

private:
    std::deque<Stop> stops_;
	std::unordered_map<std::string_view, Stop*> name_to_stop_;
    std::deque<Bus> buses_;
    std::unordered_map<std::string_view, Bus*> name_to_bus_;
};
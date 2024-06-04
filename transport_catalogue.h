/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:22:46
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-04 18:49:13
 * @FilePath: /TransportCatalogue/transport_catalogue.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <deque>
#include "geo.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Bus;
struct Stop{
    std::string name;
    Coordinates coordinates;
    
    std::vector<Bus*> buses;
};
struct Bus{
    std::string name;
    std::vector<Stop*> stops;
    double route_length;
};

class TransportCatalogue {
public:
    static constexpr std::string_view stop_cmd = {"Stop"};
    static constexpr std::string_view bus_cmd = {"Bus"};

    void AddStop(Stop&& in_stop);
    void AddBus(Bus&& in_bus);

    Stop* FindStop(std::string_view in_stop_name);
    Bus*  FindBus(std::string_view in_bus_name);

    const Bus*  FindBus(const std::string_view in_bus_name)const;
    const Stop* FindStop(const std::string_view in_stop_name)const;

    std::unordered_set<const Stop*> GetUniqueStops(const Bus* bus)const;
    std::unordered_set<const Bus*> GetUniqueBuses(const Stop* stop)const;
    size_t GetUniqueStopsCount(const Bus* bus)const;
    double ComputeRouteLength(const Bus* bus)const;
private:
    std::deque<Stop> stops_;
	std::unordered_map<std::string_view, Stop*> name_to_stop_;
    std::deque<Bus> buses_;
    std::unordered_map<std::string_view, Bus*> name_to_bus_;
};
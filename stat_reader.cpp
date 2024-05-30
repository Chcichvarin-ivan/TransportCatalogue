/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:23:30
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-30 23:50:34
 * @FilePath: /TransportCatalogue/stat_reader.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <iomanip>
#include "stat_reader.h"

using namespace std;

BusQueryResult process_query(const TransportCatalogue& tansport_catalogue, std::string_view query){
    BusQueryResult ret_val;

    const Bus* bus_request = tansport_catalogue.FindBus(query);

    ret_val.name = bus_request->name;

    if(bus_request != nullptr){
        ret_val.not_found = false;
        ret_val.stops_count = bus_request->stops.size(); 
        ret_val.unique_stops_count = tansport_catalogue.GetUniqueStopsCount(bus_request);
        ret_val.route_length = tansport_catalogue.ComputeRouteLength(bus_request);
    }else{
        ret_val.not_found = true;
    }
    return ret_val;
}

void print_result(BusQueryResult bus_info, std::ostream& output){

    if(!bus_info.not_found){
        output << "Bus " << bus_info.name << ": "
               << bus_info.stops_count << " stops on route, "
               << bus_info.unique_stops_count << " unique stops, "
               << bus_info.route_length << " route length" << std::endl;
    }else{
        output << "Bus " << bus_info.name << ": not found" << std::endl;
    }

}


void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request, std::ostream& output) {
    auto request_componets = string_view_split(request, " ");
    if(request_componets.at(0)=="Bus"){
        print_result(process_query(tansport_catalogue, request_componets.at(1)),output);
    }
}
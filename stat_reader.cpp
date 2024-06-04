/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:23:30
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-04 19:25:14
 * @FilePath: /TransportCatalogue/stat_reader.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "stat_reader.h"

using namespace std;

BusQueryResult ProcessBusQuery(const TransportCatalogue& tansport_catalogue, std::string_view bus_query){
    BusQueryResult ret_val;

    const Bus* bus_request = tansport_catalogue.FindBus(bus_query);
    ret_val.name = bus_query;
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

StopQueryResult ProcessStopQuery(const TransportCatalogue& tansport_catalogue, std::string_view stop_query){
    StopQueryResult ret_val;

    const Stop* stop_request = tansport_catalogue.FindStop(stop_query);
    ret_val.name = stop_query;
    if(stop_request != nullptr){
        ret_val.not_found = false;
        std::unordered_set<const Bus*> unique_buses = tansport_catalogue.GetUniqueBuses(stop_request);

        if(unique_buses.size() > 0){
            for (const Bus* bus : unique_buses) {
                ret_val.buses_names.push_back(bus->name);
            }
            std::sort(ret_val.buses_names.begin(),ret_val.buses_names.end());
        }

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

void print_result(StopQueryResult stop_info, std::ostream& output){
    if(!stop_info.not_found){
       if(stop_info.buses_names.size() != 0){
            output << "Stop " << stop_info.name << ": buses";
            for (std::string_view bus_name : stop_info.buses_names) {
                output << " ";
                output << bus_name;
            }
            output << std::endl;
       }else{
        output << "Stop " << stop_info.name << ": no buses" << std::endl;
       }
    }else{
        output << "Stop " << stop_info.name << ": not found" << std::endl;
    }
}


void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request, std::ostream& output) {
    auto request_componets = string_view_split(request, " ");
    if(request_componets.at(0)=="Bus"){
        print_result(ProcessBusQuery(tansport_catalogue, request.substr(request_componets.at(0).size()+1)),output);
    }else if(request_componets.at(0)=="Stop"){
        print_result(ProcessStopQuery(tansport_catalogue, request.substr(request_componets.at(0).size()+1)),output); 

    }
}
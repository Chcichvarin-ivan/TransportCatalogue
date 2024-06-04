/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:22:22
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-04 18:51:38
 * @FilePath: /TransportCatalogue/transport_catalogue.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "geo.h"
#include <stdexcept>
#include "transport_catalogue.h"

void TransportCatalogue::AddStop(Stop&& in_stop){
   stops_.push_back(std::move(in_stop));
   name_to_stop_.insert({std::string_view{stops_.back().name},&stops_.back()});
}

void TransportCatalogue::AddBus(Bus&& in_bus){
   buses_.push_back(std::move(in_bus));
   name_to_bus_.insert({std::string_view{buses_.back().name},&buses_.back()});
}

Stop* TransportCatalogue::FindStop(std::string_view in_stop_name){
   if(name_to_stop_.empty()){
      return nullptr;
   }

   try{
      return name_to_stop_.at(in_stop_name);
   } catch(const std::out_of_range &e){
      return nullptr;
   }
}

Bus* TransportCatalogue::FindBus(std::string_view  in_bus_name){
   if(name_to_bus_.empty()){
      return nullptr;
   }

   try{
      return name_to_bus_.at(in_bus_name);
   } catch(const std::out_of_range &e){
      return nullptr;
   }
} 

const Bus*  TransportCatalogue::FindBus(const std::string_view in_bus_name)const{
   if(name_to_bus_.empty()){
      return nullptr;
   }

   try{
      return name_to_bus_.at(in_bus_name);
   } catch(const std::out_of_range &e){
      return nullptr;
   }
}

const Stop* TransportCatalogue::FindStop(const std::string_view in_stop_name)const{
   if(name_to_stop_.empty()){
      return nullptr;
   }

   try{
      return name_to_stop_.at(in_stop_name);
   } catch(const std::out_of_range &e){
      return nullptr;
   }
}

std::unordered_set<const Stop*> TransportCatalogue::GetUniqueStops(const Bus* bus)const{
   std::unordered_set<const Stop*> unique_stops;
    
   unique_stops.insert(bus->stops.begin(), bus->stops.end());
    
   return unique_stops;
}


size_t TransportCatalogue::GetUniqueStopsCount(const Bus* bus) const {
   std::unordered_set<const Stop*> unique_stops;
    
   unique_stops.insert(bus->stops.begin(), bus->stops.end()); 
   return size_t(unique_stops.size());
}

double TransportCatalogue::ComputeRouteLength(const Bus* bus)const{
   double route_length = 0;

   auto stops_number = bus->stops.size() - 1;
    for (size_t iterator = 0; iterator < stops_number; iterator++) {
        route_length += ComputeDistance(bus->stops.at(iterator)->coordinates, bus->stops.at(iterator+1)->coordinates);
    }
    return route_length;
}

std::unordered_set<const Bus*> TransportCatalogue::GetUniqueBuses(const Stop* stop)const{
   std::unordered_set<const Bus*> unique_buses;

   unique_buses.insert(stop->buses.begin(),stop->buses.end());

   return unique_buses;
}
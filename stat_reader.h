/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:21:59
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-05 21:25:57
 * @FilePath: /TransportCatalogue/stat_reader.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <iosfwd>
#include <string_view>

#include "transport_catalogue.h"
namespace transport_catalogue {
namespace detail {

/**
 * Splits the given string_view into sub string_views using the given delimiter
 * @param strv std::string_view to split into parts
 * @param delim Delimiter
 * @return On success a vector of string_views is returned, otherwise an empty vector
 */
inline std::vector<std::string_view> StringViewSplit(const std::string_view& strv, const std::string& delim)
{
    std::vector<std::string_view> result;
    std::string_view strv_cpy(strv);
    size_t pos = strv_cpy.find(delim);
    if(pos == 0) { result.emplace_back(std::string_view()); }
    while( pos != std::string_view::npos )
    {
        if( pos > 0)
        { result.emplace_back(strv_cpy.substr(0, pos)); }
        strv_cpy = strv_cpy.substr(pos + 1);
        pos = strv_cpy.find(delim);
    }
    
    if( !strv_cpy.empty() )
    { result.emplace_back(strv_cpy); }
    
    return result;
}

namespace bus{
struct BusQueryResult{
    std::string_view name;
    bool not_found;
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
};

BusQueryResult ProcessBusQuery(const TransportCatalogue& tansport_catalogue, std::string_view bus_query);
}//namespace bus

namespace stop{
struct StopQueryResult{
    std::string_view name;
    bool not_found;
    std::vector <std::string_view> buses_names;
};

StopQueryResult ProcessStopQuery(const TransportCatalogue& tansport_catalogue, std::string_view stop_query);
}//end namespace stop



void PrintResult(bus::BusQueryResult bus_info, std::ostream& output);

void PrintResult(stop::StopQueryResult stop_info, std::ostream& output);

void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request,
                       std::ostream& output);
}//end namespace detail 
}//end namespace transport_catalogue
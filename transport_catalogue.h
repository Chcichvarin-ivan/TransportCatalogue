/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 00:22:46
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-06 23:10:06
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
namespace transport_catalogue { 
struct Bus;
struct Stop{
    std::string name;
    detail::geo::Coordinates coordinates;
    
    std::vector<const Bus*> buses;
};
struct Bus{
    std::string name;
    std::vector<const Stop*> stops;
    double route_length;
};

class TransportCatalogue {
public:
    static constexpr std::string_view stop_cmd = {"Stop"};
    static constexpr std::string_view bus_cmd = {"Bus"};

    void AddStop(const Stop&& in_stop);//не хватит потому что в cpp файле используется семнатика перемещения
    void AddBus(const Bus&& in_bus);

    Stop* FindStop(std::string_view in_stop_name);//нужна для заполнения вектора автобусов
    const Bus*  FindBus(const std::string_view in_bus_name)const;
    const Stop* FindStop(const std::string_view in_stop_name)const;

    //обработка запросов к базе данных вроде бы не входила в интерфейс класса справочника
    //по крайней мере так я понял из вебинара и задания
    // по условию задачи печать была вынесена в отельный модуль, я не понимаю зачем мне тащить форматирование внутрь класса
    // разделить реализации это осознанный выбор
    std::unordered_set<const Stop*> GetUniqueStops(const Bus* bus)const;// эта функция сделана по итогу анализа вебинара как задел для вычисения расстояния не по дуге сферы, я могу ее удалить но не понимаю зачем.
    std::unordered_set<const Bus*> GetUniqueBuses(const Stop* stop)const; 
    size_t GetUniqueStopsCount(const Bus* bus)const;
    double ComputeRouteLength(const Bus* bus)const;
private:
    std::deque<Stop> stops_;
	std::unordered_map<std::string_view, Stop*> name_to_stop_;
    std::deque<Bus> buses_;
    std::unordered_map<std::string_view, Bus*> name_to_bus_;
    // не очень понимаю что мне даст еще один неупорядоченный словарь, да мы делали так в задаче про автобусные расписания, но там структура была частью выполенния запроса, здесь же мы получаем дублирование памяти
    // эти данные и так хранятся в структуре остановки (строчка 22) и указатель на остановку я получаю из словаря name_to_stop, в чем прирост эфективности?
};
}//namespace transport_catalogue 
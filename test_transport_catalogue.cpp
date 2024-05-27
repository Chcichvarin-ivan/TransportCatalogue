/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-26 15:42:49
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-27 23:47:53
 * @FilePath: /TransportCatalogue/test_trancport_catalogue.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include "input_reader.h"
#include "test_transport_catalogue.h"
#include "transport_catalogue.h"
using namespace std;


/**
 * Splits the given string_view into sub string_views using the given delimiter
 * @param strv std::string_view to split into parts
 * @param delim Delimiter
 * @return On success a vector of string_views is returned, otherwise an empty vector
 */
inline std::vector<std::string_view> string_view_split(const std::string_view& strv, const std::string& delim)
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

void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line,
                const string& hint) {
    
    if (!value) {
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "Assert("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
} 

#define ASSERT_HINT(expr, hint) AssertImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
} 

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)
#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename TestFunc>
void RunTestImpl(const TestFunc& func, const string& test_name) {
    func();
    cerr << test_name << " OK"s << endl;
}

#define RUN_TEST(func) RunTestImpl(func, #func) 
// -------- Начало модульных тестов поисковой системы ----------
void TestAddStopToTheCatalogue(){
    {
        TransportCatalogue catalogue;
        Stop test_stop_in = {"Tolstopaltsevo",{55.611087,37.208290}};
        catalogue.AddStop(move(test_stop_in));
        Stop* test_stop_out = catalogue.FindStop("Tolstopaltsevo"); 
        ASSERT_HINT((test_stop_out),"FindStop should return valid pointer");
        ASSERT_EQUAL(test_stop_out->name, "Tolstopaltsevo");
        ASSERT_EQUAL(test_stop_out->coordinates.lat, 55.611087);
        ASSERT_EQUAL(test_stop_out->coordinates.lng, 37.208290);
    }
    {
        TransportCatalogue catalogue;
        Stop test_stop_in = {"Tolstopaltsevo",55.611087,37.208290};
        catalogue.AddStop(move(test_stop_in));
        test_stop_in.name = "Biryulyovo Tovarnaya";
        test_stop_in.coordinates.lat = 1;
        test_stop_in.coordinates.lng = 0;
        catalogue.AddStop(move(test_stop_in));
        test_stop_in.name = "Biryulyovo Passazhirskaya";
        test_stop_in.coordinates.lat = 0;
        test_stop_in.coordinates.lng = 1;
        catalogue.AddStop(move(test_stop_in));
        Stop* test_stop_out = catalogue.FindStop("Tolstopaltsevo"); 
        ASSERT_HINT((test_stop_out),"FindStop should return valid pointer");
        ASSERT_EQUAL(test_stop_out->name, "Tolstopaltsevo");
        ASSERT_EQUAL(test_stop_out->coordinates.lat , 55.611087);
        ASSERT_EQUAL(test_stop_out->coordinates.lng, 37.208290);
        test_stop_out = catalogue.FindStop("Biryulyovo Tovarnaya"); 
        ASSERT_HINT((test_stop_out),"FindStop should return valid pointer");
        ASSERT_EQUAL(test_stop_out->name, "Biryulyovo Tovarnaya");
        ASSERT_EQUAL(test_stop_out->coordinates.lat, 1);
        ASSERT_EQUAL(test_stop_out->coordinates.lng, 0);
        test_stop_out = catalogue.FindStop("Biryulyovo Passazhirskaya"); 
        ASSERT_HINT((test_stop_out),"FindStop should return valid pointer");
        ASSERT_EQUAL(test_stop_out->name, "Biryulyovo Passazhirskaya");
        ASSERT_EQUAL(test_stop_out->coordinates.lat, 0);
        ASSERT_EQUAL(test_stop_out->coordinates.lng, 1);
    }
    
    
}

void TestAddBusToTheCatalogue(){
    {
        TransportCatalogue catalogue;
        Bus test_bus_in;
        test_bus_in.name = "256";
        Stop test_stop_in = {"Tolstopaltsevo",55.611087,37.208290};
        catalogue.AddStop(move(test_stop_in));
        test_stop_in.name = "Biryulyovo Tovarnaya";
        test_stop_in.coordinates.lat = 1;
        test_stop_in.coordinates.lng = 0;
        catalogue.AddStop(move(test_stop_in));
        test_stop_in.name = "Biryulyovo Passazhirskaya";
        test_stop_in.coordinates.lat = 0;
        test_stop_in.coordinates.lng = 1;
        catalogue.AddStop(move(test_stop_in));
        test_bus_in.stops.push_back(catalogue.FindStop("Tolstopaltsevo"));
        test_bus_in.stops.push_back(catalogue.FindStop("Biryulyovo Tovarnaya"));
        test_bus_in.stops.push_back(catalogue.FindStop("Biryulyovo Passazhirskaya"));

        catalogue.AddBus(std::move(test_bus_in));

        Bus* test_bus_out = catalogue.FindBus("256");

        ASSERT_HINT((test_bus_out),"FindBus should return valid pointer");
        ASSERT_HINT((test_bus_out->stops.size() == 3),"there should be three stops in 256 Bus route");
        ASSERT_HINT((test_bus_out->stops.at(0) == catalogue.FindStop("Tolstopaltsevo")),"Tolstopaltsevo shold be the third stop");
        ASSERT_HINT((test_bus_out->stops.at(1) == catalogue.FindStop("Biryulyovo Tovarnaya")),"Biryulyovo Tovarnaya shold be the second stop");
        ASSERT_HINT((test_bus_out->stops.at(2) == catalogue.FindStop("Biryulyovo Passazhirskaya")),"Biryulyovo Passazhirskaya shold be the third stop");
    }
}

void TestInputReader(){
    static constexpr std::string_view input = {"Stop Tolstopaltsevo: 55.611087, 37.208290\nStop Marushkino: 55.595884, 37.209755\nBus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\nBus 750: Tolstopaltsevo - Marushkino - Rasskazovka\nStop Rasskazovka: 55.632761, 37.333324\nStop Biryulyovo Zapadnoye: 55.574371, 37.651700\nStop Biryusinka: 55.581065, 37.648390\nStop Universam: 55.587655, 37.645687\nStop Biryulyovo Tovarnaya: 55.592028, 37.653656\nStop Biryulyovo Passazhirskaya: 55.580999, 37.659164"};
    auto lines = string_view_split(input, "\n");
    TransportCatalogue catalogue;
    InputReader reader;
    
    for(auto line : lines){
        reader.ParseLine(line);
    }
    
    reader.ApplyCommands(catalogue);

    ASSERT_HINT((catalogue.FindStop("Tolstopaltsevo")->name == "Tolstopaltsevo"),"There shold be Tolstopaltsevo stop");
    ASSERT_HINT((catalogue.FindStop("Tolstopaltsevo")->coordinates.lat == 55.611087),"Tolstopaltsevo latitude should be 55.611087");
    ASSERT_HINT((catalogue.FindStop("Tolstopaltsevo")->coordinates.lng == 37.208290),"Tolstopaltsevo latitude should be 37.208290");

    ASSERT_HINT((catalogue.FindStop("Marushkino")->name == "Marushkino"),"There shold be Marushkino stop");
    ASSERT_HINT((catalogue.FindStop("Marushkino")->coordinates.lat == 55.595884),"Marushkino latitude should be 55.595884");
    ASSERT_HINT((catalogue.FindStop("Marushkino")->coordinates.lng == 37.209755),"Marushkino latitude should be 37.209755");


    ASSERT_HINT((catalogue.FindStop("Biryulyovo Zapadnoye")->name == "Biryulyovo Zapadnoye"),"There shold be Biryulyovo Zapadnoye stop");
    ASSERT_HINT((catalogue.FindStop("Biryulyovo Zapadnoye")->coordinates.lat == 55.574371),"Biryulyovo Zapadnoye latitude should be 55.574371");
    ASSERT_HINT((catalogue.FindStop("Biryulyovo Zapadnoye")->coordinates.lng == 37.651700),"Biryulyovo Zapadnoye latitude should be 37.651700");

    ASSERT_HINT((catalogue.FindStop("Rasskazovka")->name == "Rasskazovka"),"There shold be Rasskazovka stop");
    ASSERT_HINT((catalogue.FindStop("Rasskazovka")->coordinates.lat == 55.632761),"Rasskazovka latitude should be 55.632761");
    ASSERT_HINT((catalogue.FindStop("Rasskazovka")->coordinates.lng == 37.333324),"Rasskazovka latitude should be 37.333324");
    
    ASSERT_HINT((catalogue.FindStop("Biryusinka")->name == "Biryusinka"),"There shold be Biryusinka stop");
    ASSERT_HINT((catalogue.FindStop("Biryusinka")->coordinates.lat == 55.581065),"Biryusinka latitude should be 55.581065");
    ASSERT_HINT((catalogue.FindStop("Biryusinka")->coordinates.lng == 37.648390),"Biryusinka latitude should be 37.648390");

    ASSERT_HINT((catalogue.FindStop("Universam")->name == "Universam"),"There shold be Universam stop");
    ASSERT_HINT((catalogue.FindStop("Universam")->coordinates.lat == 55.587655),"Universam latitude should be 55.587655");
    ASSERT_HINT((catalogue.FindStop("Universam")->coordinates.lng == 37.645687),"Universam latitude should be 37.645687");

    ASSERT_HINT((catalogue.FindStop("Biryulyovo Tovarnaya")->name == "Biryulyovo Tovarnaya"),"There shold be Biryulyovo Tovarnaya stop");
    ASSERT_HINT((catalogue.FindStop("Biryulyovo Tovarnaya")->coordinates.lat == 55.592028),"Universam latitude should be 55.592028");
    ASSERT_HINT((catalogue.FindStop("Biryulyovo Tovarnaya")->coordinates.lng == 37.653656),"Universam latitude should be 37.653656");

    ASSERT_HINT((catalogue.FindStop("Biryulyovo Passazhirskaya")->name == "Biryulyovo Passazhirskaya"),"There shold be Biryulyovo Tovarnaya stop");
    ASSERT_HINT((catalogue.FindStop("Biryulyovo Passazhirskaya")->coordinates.lat == 55.580999),"Universam latitude should be 55.580999");
    ASSERT_HINT((catalogue.FindStop("Biryulyovo Passazhirskaya")->coordinates.lng == 37.659164),"Universam latitude should be 37.659164");

    ASSERT_HINT((catalogue.FindBus("256")->name == "256"),"There shold be 256 Bus");
    ASSERT_HINT((catalogue.FindBus("256")->stops.size() == 6),"There shold be 6 stops in 256 Bus route");
    ASSERT_HINT((catalogue.FindBus("256")->stops.at(0)->name == "Biryulyovo Zapadnoye"),"First stop of the 256 Bus route should be Biryulyovo Zapadnoye");       
    ASSERT_HINT((catalogue.FindBus("256")->stops.at(1)->name == "Biryusinka"),"Second stop of the 256 Bus route should be Biryusinka");
    ASSERT_HINT((catalogue.FindBus("256")->stops.at(2)->name == "Universam"),"Third stop of the 256 Bus route should be Universam");
    ASSERT_HINT((catalogue.FindBus("256")->stops.at(3)->name == "Biryulyovo Tovarnaya"),"Fourth stop of the 256 Bus route should be Biryulyovo Tovarnaya");
    ASSERT_HINT((catalogue.FindBus("256")->stops.at(4)->name == "Biryulyovo Passazhirskaya"),"Fifth stop of the 256 Bus route should be Biryulyovo Passazhirskaya");
    ASSERT_HINT((catalogue.FindBus("256")->stops.at(5)->name == "Biryulyovo Zapadnoye"),"Last stop of the 256 Bus route should be Biryulyovo Zapadnoye");
}
// Функция TestTranspotCatalogue является точкой входа для запуска тестов
void TestTranspotCatalogue(void){
    RUN_TEST(TestAddStopToTheCatalogue);
    RUN_TEST(TestAddBusToTheCatalogue);
    RUN_TEST(TestInputReader);
}
// --------- Окончание модульных тестов поисковой системы -----------

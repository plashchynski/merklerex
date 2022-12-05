#pragma once

#include <string>

enum class OrderBookType{bid, ask, sale, unknown};

class OrderBookEntry
{
    public:

        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType);

        static OrderBookType stringToOrderBookType(std::string s);

        static bool compareByTimestamps(OrderBookEntry& el1, OrderBookEntry& el2);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
};
 

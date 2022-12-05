#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
  public:
    /** construct, reading a csv data file */
    OrderBook(std::string filename);
    /** return a vector of all known products in the dataset */
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    static double getHighPrice(std::vector<OrderBookEntry> & orders);
    static double getLowPrice(std::vector<OrderBookEntry> & orders);
    static double getMeanPrice(std::vector<OrderBookEntry> & orders);
    static double getStdPrice(std::vector<OrderBookEntry> & orders);
    std::string getEarliestTime();
    std::string getNextTime(std::string timestamp);
    void insertOrder(OrderBookEntry& order);
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
  private:
    std::vector<OrderBookEntry> orders;
};

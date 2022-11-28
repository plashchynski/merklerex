#include <vector>
#include <map>
#include <cmath>

#include "OrderBook.h"
#include "CSVReader.h"

/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
  orders = CSVReader::readCSV(filename);
}

/** return a vector of all known products in the dataset */
std::vector<std::string> OrderBook::getKnownProducts()
{
  std::vector<std::string> products;

  std::map<std::string, bool> prodMap;

  for(OrderBookEntry& e : orders)
  {
    prodMap[e.product] = true;
  }

  for (auto const & e : prodMap)
  {
    products.push_back(e.first);
  }

  return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                      std::string product,
                                      std::string timestamp)
{
  std::vector<OrderBookEntry> orders_sub;


  for (OrderBookEntry& e : orders)
  {
    if (e.orderType == type && e.product == product && e.timestamp == timestamp)
    {
      orders_sub.push_back(e);
    }
  }

  return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> & orders)
{
  double max = orders[0].price;
  for (OrderBookEntry &e : orders)
  {
    if (e.price > max)
      max = e.price;
  }
  return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> & orders)
{
  double min = orders[0].price;
  for (OrderBookEntry &e : orders)
  {
    if (e.price < min)
      min = e.price;
  }
  return min;
}

/**
 * @brief Get the Mean price from a vector of orders
 */
double OrderBook::getMeanPrice(std::vector<OrderBookEntry> & orders)
{
  double sum = 0;
  for (OrderBookEntry &e : orders)
  {
      sum += e.price;
  }
  return sum / orders.size();
}

/**
 * @brief Get the standard deviation of prices from a vector of orders
 */
double OrderBook::getStdPrice(std::vector<OrderBookEntry> & orders)
{
  double mean = getMeanPrice(orders);
  double sum = 0;
  for (OrderBookEntry &e : orders)
  {
      sum += pow(e.price - mean, 2);
  }
  return sqrt(sum);
}

std::string OrderBook::getEarliestTime()
{
  return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
  std::string next_time_stamp = "";
  for (OrderBookEntry &e : orders)
  {
    if (e.timestamp > timestamp)
    {
      next_time_stamp = e.timestamp;
      break;
    }
  }
  if (next_time_stamp == "")
  {
    next_time_stamp = orders[0].timestamp;
  }
  return next_time_stamp;
}
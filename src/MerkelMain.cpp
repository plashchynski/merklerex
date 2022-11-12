#include <iostream>
#include <vector>
#include "MerkelMain.h"
#include "OrderBookEntry.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    loadOrderBook();
    int input;
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
    
}

void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;

    std::cout << "============== " << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

double computeLowPrice(std::vector<OrderBookEntry>& entries)
{
    double lowPrice = entries[0].price;

    for (unsigned int i = 1; i < entries.size(); ++i)
    {
        if (entries[i].price < lowPrice)
        {
            lowPrice = entries[i].price;
        }
    }

    return lowPrice;
}

double computeHighPrice(std::vector<OrderBookEntry>& entries)
{
    double highPrice = entries[0].price;

    for (unsigned int i = 1; i < entries.size(); ++i)
    {
        if (entries[i].price > highPrice)
        {
            highPrice = entries[i].price;
        }
    }

    return highPrice;
}

double computeAveragePrice(std::vector<OrderBookEntry>& entries)
{
    double sum = 0;

    for (OrderBookEntry& entry : entries)
    {
        sum += entry.price;
    }

    return (sum / entries.size());
}


double computePriceSpread(std::vector<OrderBookEntry>& entries)
{
    double lowPrice = computeLowPrice(entries);
    double highPrice = computeHighPrice(entries);

    return (highPrice - lowPrice);
}

void  MerkelMain::printMarketStats()
{
    std::cout << "Order book contains: " << orders.size() << " entries." << std::endl;

    std::cout << "The average price is: " << computeAveragePrice(orders) << std::endl;
    std::cout << "The low price is: " << computeLowPrice(orders) << std::endl;
    std::cout << "The high price is: " << computeHighPrice(orders) << std::endl;
    std::cout << "The price spread is: " << computePriceSpread(orders) << std::endl;
}

void MerkelMain::enterOffer()
{
    std::cout << "Mark and offer - enter the amount " << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "Your wallet is empty. " << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
}
 
int MerkelMain::getUserOption()
{
    int userOption;

    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) // bad input
    {
        printHelp();
    }
    if (userOption == 2) // bad input
    {
        printMarketStats();
    }
    if (userOption == 3) // bad input
    {
        enterOffer();
    }
    if (userOption == 4) // bad input
    {
        enterBid();
    }
    if (userOption == 5) // bad input
    {
        printWallet();
    }
    if (userOption == 6) // bad input
    {
        gotoNextTimeframe();
    }       
}

void MerkelMain::loadOrderBook()
{
    orders.push_back(OrderBookEntry{100.0, 1.0, "2018-01-01 12:00:00", "BTC/USD", OrderBookType::bid});
    orders.push_back(OrderBookEntry{101.0, 1.0, "2018-01-01 12:00:00", "BTC/USD", OrderBookType::bid});
    orders.push_back(OrderBookEntry{112.0, 1.0, "2018-01-01 12:00:00", "BTC/USD", OrderBookType::bid});
    orders.push_back(OrderBookEntry{132.0, 1.0, "2018-01-01 12:00:00", "BTC/USD", OrderBookType::bid});
}

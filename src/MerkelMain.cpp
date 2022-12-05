#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{


}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    while(true)
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

void MerkelMain::printMarketStats()
{
    for (const std::string & product : orderBook.getKnownProducts())
    {
        std::cout << "Product " << product << std::endl;

        std::vector<OrderBookEntry> entries = orderBook.getOrders(
            OrderBookType::ask, product, currentTime);

        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask : " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask : " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Mean ask : " << OrderBook::getMeanPrice(entries) << std::endl;
        std::cout << "STD ask : " << OrderBook::getStdPrice(entries) << std::endl;
    }    
}

void MerkelMain::enterOffer()
{
    std::cout << "Mark and offer - enter the amount: product,price,amount " << std::endl;
    std::string input;

    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Bad input:" << input << std::endl;
        return;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2],
                                            currentTime, tokens[0], OrderBookType::ask);
            orderBook.insertOrder(obe);
        } catch(const std::exception& e)
        {
            std::cout << "Bad input:" << input << std::endl;
            return;
        }   
    }
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
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Current time is: " << currentTime << std::endl;
}
 
int MerkelMain::getUserOption()
{
    int userOption;
    std::string line;

    std::cout << "Type in 1-6" << std::endl;

    std::getline(std::cin, line);

    try {
        userOption = std::stoi(line);
    } catch(const std::exception& e)
    {
        std::cout << "Bad input:" << line << std::endl;
        return 0;
    }

    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        enterOffer();
    }
    if (userOption == 4) 
    {
        enterBid();
    }
    if (userOption == 5) 
    {
        printWallet();
    }
    if (userOption == 6) 
    {
        gotoNextTimeframe();
    }       
}
 

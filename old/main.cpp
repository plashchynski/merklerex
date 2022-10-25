#include <iostream>
#include <map>

void printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;

    // 2 print exchange stats
    std::cout << "2: Print exchange stats " << std::endl;

    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;

    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;

    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;

    // 6 continue
    std::cout << "6: Continue " << std::endl;

    std::cout << "=================================" << std::endl;

    std::cout << "Type in 1-6" << std::endl;
}

int getUserOption()
{
    int userOption;

    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;

    return userOption;
}

void printHelp()
{
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void printMarketStats()
{
    std::cout << "Exchange stats - here you can see the current exchange stats." << std::endl;
}

void enterAsk()
{
    std::cout << "Make an offer - here you can make an offer." << std::endl;
}

void enterBid()
{
    std::cout << "Make a bid - here you can make a bid." << std::endl;
}

void printWallet()
{
    std::cout << "Your wallet is empty" << std::endl;
}

void gotoNextTimeFrame()
{
    std::cout << "Goint to next timeframe" << std::endl;
}

void processUserOption(int userOption)
{
    // map from ints to function pointers
    std::map<int,void(*)()> menu;
    menu[1] = printHelp;
    menu[2] = printMarketStats;
    menu[3] = enterAsk;
    menu[4] = enterBid;
    menu[5] = printWallet;
    menu[6] = gotoNextTimeFrame;

    // check if the key exists
    if (menu.count(userOption) > 0)
    {
        menu[userOption]();
    }

    std::cout << "Invalid option" << std::endl;
    return;
}

int main()
{
    while (true) {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }
    return 0;
}

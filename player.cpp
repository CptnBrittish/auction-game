#include "player.h"
#include "bid.h"
#include "limits.h"

#include "iostream"


player::player(){
    setTraderName(std::string("Player"));
    setTraderMoney(200);
    setMoneyLeft(getTraderMoney());
}

std::vector<bid> player::generateBid(){
    std::vector<bid> Bid;
    bool moreBids = true;
    while(moreBids){
	bid newBid;

	newBid.setTraderName(getName());
	std::cout << "Please choose type of bid:\nA = Sell\nB = buy\n> ";
	char type;
	std::cin >> type;
	newBid.setBidType(type);

	double price;
	std::cout << "Set bid price: ";
	std::cin >> price;
	newBid.setBidPrice(price);

	std::string name;
	std::cout << "Set item name: ";
	std::cin >> name;
	newBid.setItemName(name);

	int quantity;
	std::cout << "Set quantity: ";
	std::cin >> quantity;
	newBid.setBidQuantity(quantity);
	Bid.push_back(newBid);

	std::cout << "\nMake another bid? (y/n)";
	char continueBids;
	std::cin >> continueBids;
	if(continueBids == 'y'){
	    moreBids = true;
	} else {
	    moreBids = false;
	}
    }
    return Bid;
}

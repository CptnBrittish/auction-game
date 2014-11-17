#include "player.h"
#include "bid.h"
#include "limits.h"
#include "parseInput.h"

#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string>

player::player(){
    setTraderName(std::string("Player"));
    setTraderMoney(200);
    setMoneyLeft(getTraderMoney());
}

std::vector<bid> player::generateBid(){
    
    std::string input;
    std::vector<bid> Bid;
    bool moreBids = true;
    
    while(moreBids){
	bid newBid;

	newBid.setTraderName(getName());

	std::string type;
	while((type.compare(std::string("A")) != 0) && (type.compare(std::string("B")) != 0)){
	    std::cout << "Please choose type of bid:\nA = Sell\nB = buy\n> ";
	    getline(std::cin, type);
	    //type.assign(input);
	    //for(int i = type.length()-1; i >=0; i--){
	    //type[i] = toupper(type[i]);
	    //}
	    if((type.compare("A") != 0) && (type.compare("B") != 0)){
		std::cout << "Invalid Input please try again\n";
	    }
	}
	newBid.setBidType(type[1]);
	
	double price = -1;
	while(price == -1){
	    std::cout << "Set bid price: ";
	    getline(std::cin, input);
	    price = validateIsADouble(input);
	    if(price == -1){
		std::cout << "Invalid Input please try again\n";
	    }
	}
	newBid.setBidPrice(price);
	
	std::string name = "-1";
	while(name == "-1"){
	    std::cout << "Set item name: ";
	    getline(std::cin, input);
	    name = validateIsAString(input);
	    if(name == "-1"){
		std::cout << "Invalid Input please try again\n";
	    }
	}
	newBid.setItemName(name);

	int quantity = -1;
	while(quantity == -1){
	    std::cout << "Set quantity: ";
	    getline(std::cin, input);
	    quantity = validateIsANumber(input);
	    if(quantity == -1){
		std::cout << "Invalid input please try again\n";

	    }
	}
	newBid.setBidQuantity(quantity);

	Bid.push_back(newBid);

	std::cout << "\nMake another bid? (y/n)";
	char continueBids;
	while((continueBids != 'y') && (continueBids != 'n')){
	    getline(std::cin, input);
	    continueBids = input[0];
	    if((continueBids != 'y') && (continueBids != 'n')){
		std::cout << "Invalid input please try again\n";
	    }

	}
	if(continueBids == 'y'){
	    moreBids = true;
	} else {
	    moreBids = false;
	}
    }
    return Bid;
}

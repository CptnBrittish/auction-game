#include "trader.h"
#include "matchStructs.h"
#include "limits.h"

#include <string>
#include <iostream>
#include <stdlib.h>
 
trader::trader(){
    traderName.assign(std::string("Temporary Name"));
    traderType = 'A';
}

trader::trader(const char * name, char type){
    traderName.assign(std::string(name));
    traderType = type;
}

trader::trader(std::string name, char type){
    traderName.assign(name);
    traderType = type;
}

trader::~trader(){
}

std::string trader::getName(){
    return traderName;
}

char trader::getType(){
    return traderType;
}

bid trader::generateBid(){
    traderBid.setBidPrice(rand() % (MAXPRICE - MINPRICE) + MINPRICE);

    traderBid.setTraderName(traderName);
    traderBid.setBidType(traderType);

    //We set this anyway but there is no need to the auctionmaster deals with the bidIds after they are handed in
	traderBid.setBidId(0);

    return traderBid;
}

void trader::getMatchedBid(matchedBid matched){
    std::cout << "Trader Name: " << getName() << std::endl
	      << "Received Match" << std::endl;
    if(getType() == 'A'){
	std::cout << "Matched with: " << matched.matchedTraderOne << std::endl;
    } else {
	std::cout << "Matched with: " << matched.matchedTraderTwo << std::endl;
    }
    std::cout << "With a clearing price of: " << matched.clearingPrice << std::endl
	      << std::endl;
}

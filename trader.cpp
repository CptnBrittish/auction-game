#include "trader.h"
#include "match.h"
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

std::vector<bid> trader::generateBid(){
    //We want to cap at ten bids set in limits.h
    for(int numBids = MAXBIDS; numBids>=0; numBids--){
	bid Bid;
	Bid.setBidPrice(rand() % (MAXPRICE - MINPRICE) + MINPRICE);
	//cap bid quantity at 200
	Bid.setBidQuantity(rand() % MAXBIDQUANTITY+1);
	Bid.setTraderName(traderName);
	Bid.setBidType(traderType);

	//We set this anyway but there is no need to the auctionmaster deals with the bidIds after they are handed in
	Bid.setBidId(0);
	traderBids.push_back(Bid);
    }

    return traderBids;
}

void trader::getMatchedBid(matchedBid matched){
    std::cout << "Trader Name: " << getName() << std::endl
	      << "Received Match" << std::endl;
    // We want to find the opposite type to us
    std::cout << "Bid Id: " << matched.bidId << std::endl;
    if(getType() == 'B'){
	std::cout << "Matched with: " << matched.sellerName << std::endl;
    } else {
	std::cout << "Matched with: " << matched.buyerName << std::endl;
    }
    std::cout << "With a clearing price of: " << matched.clearingPrice << std::endl;
    std::cout << "For the quantity of: " << matched.quantity << std::endl
	      << std::endl;
}

#include "trader.h"
#include "match.h"
#include "limits.h"
#include "item.h"

#include <string>
#include <iostream>
#include <stdlib.h>

trader::trader(){
    traderName.assign(std::string("Temporary Name"));
    traderType = 'B';
    money = rand() % (MAXPRICE - MINPRICE) + MINPRICE;
    moneyLeftForBids = money;
}

trader::trader(const char * name, char type){
    traderName.assign(std::string(name));
    traderType = type;
    money = rand() % (MAXPRICE - MINPRICE) + MINPRICE;
    moneyLeftForBids = money;
    //Add a random amount of inventory to the trader
    if(traderType == 'A'){
	for(int i = rand() % 3+1; i>=0; i--){
	    item newItem;
	    newItem.itemName = itemNameOptions[i];
	    newItem.description = itemDescriptionOptions[i];
	    newItem.quantity = rand() % MAXBIDQUANTITY+1;

	    inventory.push_back(newItem);
	}
	condenseInventory();
    }
}

trader::trader(std::string name, char type){
    traderName.assign(name);
    traderType = type;
    money = rand() % (MAXPRICE - MINPRICE) + MINPRICE;
    moneyLeftForBids = money;
}

trader::~trader(){
}

std::string trader::getName(){
    return traderName;
}

void trader::setTraderName(std::string name){
    traderName.assign(name);
}

void trader::setTraderMoney(double newMoney){
    money = newMoney;
}


double trader::getTraderMoney(){
    return money;
}

void trader::setMoneyLeft(double newMoney){
    moneyLeftForBids = newMoney;
}

double trader::getMoneyLeft(){
    return moneyLeftForBids;
}


char trader::getType(){
    return traderType;
}

std::vector<bid> trader::generateBid(){
    //We need to make sure we have a inventory first
    //We want to cap at ten bids set in limits.h
    for(int numBids = MAXBIDS; numBids>=0; numBids--){
	if(traderType == 'B'){
	    if(int(moneyLeftForBids) >= 1){
		bid Bid;

		Bid.setBidPrice(rand() % int(moneyLeftForBids));
	
		// Reduce money left for bids
		moneyLeftForBids = moneyLeftForBids - Bid.getBidPrice(); 	

		//Add a item to bid for
		Bid.setItemName(itemNameOptions[rand() % 3+1]);		
		
		//cap bid quantity at 200
		Bid.setBidQuantity(rand() % MAXBIDQUANTITY+1);		
		Bid.setTraderName(traderName);
		Bid.setBidType(traderType);

		//We set this anyway but there is no need to the auctionmaster deals with the bidIds after they are handed in
		Bid.setBidId(0);
		traderBids.push_back(Bid);
	    }
	} else {
	    bid Bid;
	    Bid.setBidPrice(rand() % int(moneyLeftForBids));

	    int inventoryItemToUse = rand() % (int)inventory.size();
	    //Add a item to bid for
	    Bid.setItemName(inventory[inventoryItemToUse].itemName); 	    
	    Bid.setBidQuantity(rand() % inventory[inventoryItemToUse].quantity+1);
	    
	    Bid.setTraderName(traderName);
	    Bid.setBidType(traderType);

	    //We set this anyway but there is no need to the auctionmaster deals with the bidIds after they are handed in
	    Bid.setBidId(0);
	    traderBids.push_back(Bid);
	}

	return traderBids;
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
    std::cout << "The Item of: " << matched.itemName << std::endl;
    std::cout << "With a clearing price of: " << matched.clearingPrice << std::endl;
    std::cout << "For the quantity of: " << matched.quantity << std::endl
	      << std::endl;
    matchedBids.push_back(matched);
}

int trader::sendMoneyToEscrow(int matchId){
    for(int i = matchedBids.size()-1; i>=0; i--){
	if(matchedBids[i].matchId == matchId){
	    money = money - matchedBids[i].clearingPrice;
	    int tempMoney = matchedBids[i].clearingPrice;
	    matchedBids.erase(matchedBids.begin() + i);
	    return tempMoney;
	}
    }
    //control shouldnt reach here
    return -1;
}

void trader::getMoneyFromEscrow(int escrowMoney, int matchId){
    money = money + escrowMoney;
    for(int i = matchedBids.size()-1; i>=0; i--){
	if(matchedBids[i].matchId == matchId){
	    matchedBids.erase(matchedBids.begin() + i);
	}
    }
}

//Merge duplicate entrys in the inventory
void trader::condenseInventory(){
    for(int i = inventory.size()-1; i>=0; i--){
	for(int j = inventory.size()-1; i>=0; i--){
	    if(i == j){
		break;
	    } else if(inventory[i].itemName == inventory[j].itemName){
		inventory[i].quantity += inventory[j].quantity;
		inventory.erase(inventory.begin() + j);
	    }
	}
    }
}

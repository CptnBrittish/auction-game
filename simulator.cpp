#include "simulator.h"
#include "trader.h"
#include "match.h"
#include "player.h"
#include "display.h"
#include "limits.h"
#include "item.h"

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

simulator::simulator(){
    Display = new display(&Items);
    Player = new player(&Items);
    
    //Get list of trader name options from file and then instantiate traders
    std::vector<std::string> firstNames;
    std::vector<std::string> lastNames;
    //Read from trader name file once for info
    std::ifstream traderNameFile;
    traderNameFile.open("traderNames");
    std::string line;
    while(std::getline(traderNameFile, line)){
	if(line[0] == ':'){
	    if(line == ":first"){
		while(line != ":start"){
		    getline(traderNameFile,line);
		}
		getline(traderNameFile, line);
		while(line != ":end"){
		    firstNames.push_back(line);
		    std::cout << line << std::endl;
		    std::getline(traderNameFile, line);
		}
	    }
	    std::cout << "End first names" << std::endl;
	    if(line == ":last"){
		while(line != ":start"){
		    getline(traderNameFile,line);
		}
		getline(traderNameFile,line);
		while(line != ":end"){
		    lastNames.push_back(line);
		    std::cout << line << std::endl;
		    std::getline(traderNameFile, line);
		}
	    }
	}
    }

    //Add the trader information here
    for(int numBuyers = NUMBUYER; numBuyers >= 1; numBuyers--){
	Traders.push_back(trader(getTraderName(firstNames, lastNames), 'B'));
    }

    for(int numSellers = NUMSELLER; numSellers >= 1; numSellers--){
	Traders.push_back(trader(getTraderName(firstNames, lastNames), 'A'));
    }
    traderNameFile.close();
}

simulator::~simulator(){
}

std::string simulator::getTraderName(std::vector<std::string> &firstNames, std::vector<std::string> &lastNames){
    return firstNames[rand() % (firstNames.size()-1)] + " " + lastNames[rand() % (lastNames.size()-1)];
}

void simulator::runSimulator(){
    collectBids();
    distributeBids();
    getAndDistributeMatches();
    getEscrowMoney();
    distributeEscrowMoney();
}

void simulator::collectBids(){
    //for each trader we need to collect bids and add them to our array of bids
    for(int i = Traders.size()-1; i >=0; i--){
	std::vector<bid> traderBids = Traders[i].generateBid();
	for(int j = traderBids.size()-1; j>=0; j--){
	    Bid.push_back(traderBids[j]);
	}
    }
    std::vector<bid> playerBid = Player->generateBid();
    for(int i = playerBid.size()-1; i >=0; i--){
	Bid.push_back(playerBid[i]);
		     
    }
}

void simulator::distributeBids(){
    //Give our array of bids to the auctionmaster
    for(int i = Bid.size()-1; i >= 0; i--){
	bid bidToPass = Bid[i];
	auctionMaster.getBid(bidToPass);
    }
    Display->showBids(auctionMaster.getBuyerBids(), auctionMaster.getSellerBids());
}

void simulator::getAndDistributeMatches(){
    auctionMaster.matchBids();
    //Get matches from auctionmaster
    matchedBids = auctionMaster.distributeMatches();
    Display->showMatches(matchedBids);
    //send match to the trader
    for(int j = matchedBids.size()-1; j >= 0; j--){
	for(int i = NUMTRADERS-1; i >= 0; i--){
	    if(matchedBids[j].buyerName == Traders[i].getName()){
		Traders[i].getMatchedBid(matchedBids[j]);
	    }
	    if(matchedBids[j].buyerName == Player->getName()){
		Player->getMatchedBid(matchedBids[j]);
	    }
	    if(matchedBids[j].sellerName == Traders[i].getName()){
		Traders[i].getMatchedBid(matchedBids[j]);
	    }
	    if(matchedBids[j].sellerName == Player->getName()){
		Player->getMatchedBid(matchedBids[j]);
	    }
	}
    }

}

void simulator::getEscrowMoney(){
    for(int i = matchedBids.size()-1; i >= 0; i--){
	for(int j = Traders.size()-1; j >= 0; j--){
	    if(matchedBids[i].buyerName == Traders[j].getName()){
		auctionMaster.addMoneyToEscrow(Traders[j].sendMoneyToEscrow(matchedBids[i].matchId), matchedBids[i].matchId);
	    }
	}
	if(matchedBids[i].buyerName == Player->getName()){
	    auctionMaster.addMoneyToEscrow(Player->sendMoneyToEscrow(matchedBids[i].matchId), matchedBids[i].matchId);
	}
    }
}

void simulator::distributeEscrowMoney(){
    for(int i = matchedBids.size()-1; i >= 0; i--){
	for(int j = Traders.size()-1; j >= 0; j--){
	    if(matchedBids[i].sellerName == Traders[j].getName()){
		Traders[j].getMoneyFromEscrow(auctionMaster.removeMoneyFromEscrow(matchedBids[i].matchId, matchedBids[i].sellerName),
					      matchedBids[i].matchId);
		matchedBids.erase(matchedBids.begin() + i);
	    }
	}
	if(matchedBids[i].sellerName == Player->getName()){
	    Player->getMoneyFromEscrow(auctionMaster.removeMoneyFromEscrow(matchedBids[i].matchId, matchedBids[i].sellerName),
				      matchedBids[i].matchId);
	    matchedBids.erase(matchedBids.begin() + i);
	}
    }
}

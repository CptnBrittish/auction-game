#include "simulator.h"
#include "trader.h"
#include "match.h"

#include <vector>

simulator::simulator(){
    //Add the trader information here
    Traders.push_back(trader("Thomas Atkinson", 'A'));
    Traders.push_back(trader("Thomas Quinn", 'A'));
    Traders.push_back(trader("Tori Clarke", 'A'));
    Traders.push_back(trader("Jarrod Briggs", 'A'));
    Traders.push_back(trader("James Lynch", 'A'));
    Traders.push_back(trader("Micheal Selby", 'A'));
    Traders.push_back(trader("Tegan Leahy", 'A'));
    Traders.push_back(trader("Kiani Denoord", 'A'));
    Traders.push_back(trader("Lenny Nesbit", 'A'));
    Traders.push_back(trader("Maria Nesbit", 'A'));

    Traders.push_back(trader("Ben Atkinson", 'B'));
    Traders.push_back(trader("Sam Kennedy", 'B'));
    Traders.push_back(trader("Chriss Quinn", 'B'));
    Traders.push_back(trader("John Smith", 'B'));
    Traders.push_back(trader("Tim Drummond", 'B'));
    Traders.push_back(trader("Ryan Hinton", 'B'));
    Traders.push_back(trader("Katherine Pettit", 'B'));
    Traders.push_back(trader("John Cuthill", 'B'));
    Traders.push_back(trader("Caitlin Langerak", 'B'));
    Traders.push_back(trader("Emily Abbott", 'B'));
}

simulator::~simulator(){
}

void simulator::collectBids(){
    //for each trader we need to collect bids and add them to our array of bids
    for(int i = NUMTRADERS-1; i >=0; i--){
	std::vector<bid> traderBids = Traders[i].generateBid();
	for(int i = traderBids.size()-1; i>=0; i--){
	    Bid.push_back(traderBids[i]);
	}
    }
}

void simulator::distributeBids(){
    //Give our array of bids to the auctionmaster
    for(int i = Bid.size()-1; i >= 0; i--){
	bid bidToPass = Bid[i];
    auctionMaster.getBid(bidToPass);
    }
    auctionMaster.announceBids();
}

void simulator::getAndDistributeMatches(){
    auctionMaster.matchBids();
    auctionMaster.announceMatches();
    //Get matches from auctionmaster
    std::vector<matchedBid> matchToDistribute = auctionMaster.distributeMatches();

    //send match to the trader
    for(int j = auctionMaster.getNumMatches()-1; j >= 0; j--){
	for(int i = NUMTRADERS-1; i >= 0; i--){
	    if(matchToDistribute[j].buyerName == Traders[i].getName()){
		Traders[i].getMatchedBid(matchToDistribute[j]);
	    }
	    if(matchToDistribute[j].sellerName == Traders[i].getName()){
		Traders[i].getMatchedBid(matchToDistribute[j]);
	    }
	}
    }

}

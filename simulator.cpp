#include "simulator.h"
#include "trader.h"
#include "matchStructs.h"

simulator::simulator(){
    //Add the trader information here
    Traders[0] = new trader("Thomas Atkinson", 'A');
    Traders[1] = new trader("Thomas Quinn", 'A');
    Traders[2] = new trader("Tori Clarke", 'A');
    Traders[3] = new trader("Jarrod Briggs", 'A');
    Traders[4] = new trader("James Lynch", 'A');
    Traders[5] = new trader("Micheal Selby", 'A');
    Traders[6] = new trader("Tegan Leahy", 'A');
    Traders[7] = new trader("Kiani Denoord", 'A');
    Traders[8] = new trader("Lenny Nesbit", 'A');
    Traders[9] = new trader("Maria Nesbit", 'A');

    Traders[10] = new trader("Ben Atkinson", 'B');
    Traders[11] = new trader("Sam Kennedy", 'B');
    Traders[12] = new trader("Chriss Quinn", 'B');
    Traders[13] = new trader("John Smith", 'B');
    Traders[14] = new trader("Tim Drummond", 'B');
    Traders[15] = new trader("Ryan Hinton", 'B');
    Traders[16] = new trader("Katherine Pettit", 'B');
    Traders[17] = new trader("John Cuthill", 'B');
    Traders[18] = new trader("Caitlin Langerak", 'B');
    Traders[19] = new trader("Emily Abbott", 'B');
}

simulator::~simulator(){
}

void simulator::collectBids(){
    //for each trader we need to collect bids and add them to our array of bids
    for(int i = NUMTRADERS-1; i >=0; i--){
	*Bid[i] = *Traders[i]->generateBid();
    }
}

void simulator::distributeBids(){
    //Give our array of bids to the auctionmaster
    auctionMaster.getBid(*Bid);
}

void simulator::getAndDistributeMatches(){
    matchedBid * matchToDistribute = new matchedBid[auctionMaster.getNumMatches()];
    //Get matches from auctionmaster
    matchToDistribute = auctionMaster.distributeMatches();

    //send match to the trader
    for(int j = auctionMaster.getNumMatches(); j >= 0; j--){
	for(int i = NUMTRADERS-1; i >= 0; i--){
	    if(matchToDistribute[j].matchedTraderOne == Traders[i]->getName()){
		Traders[i]->getMatchedBid(matchToDistribute);
	    }
	}
    }

}

#include "auctioneer.h"
#include "bid.h"
#include "matchStructs.h"

#include <iostream>

using namespace std;

auctioneer::auctioneer(){
}

auctioneer::~auctioneer(){
    delete[] &buyerBids;
    delete[] &sellerBids;

    delete[] matches;
}

void auctioneer::getBid(bid *Bid){
    int id = 1;
    if(Bid->getBidType() == 'A'){
	while(sellerBids[id-1]->getBidId() != 0){
	    id++;
	}
	Bid->setBidId(id);
	*sellerBids[id-1] = *Bid;
    }
    if(Bid->getBidType() == 'B'){
	while(buyerBids[id-1]->getBidId() != 0){
	    id++;
	}
	Bid->setBidId(id);
	*buyerBids[id-1] = *Bid;
    }

}

void auctioneer::matchBids(){
    int buyerMatchId = NUMBUYER;
    bool foundBuyer = false;

    for(int seller = NUMSELLER; seller >= 0; seller--){
	for(int buyer = NUMBUYER; buyer >= 0; buyer--){
	    if(sellerBids[seller]->getBidPrice() <= buyerBids[buyer]->getBidPrice()){
		if(buyerBids[buyer]->getBidPrice() > buyerBids[buyerMatchId]->getBidPrice()){
		    buyerMatchId = buyer;
		    foundBuyer = true;
		}
	    }
	    if(foundBuyer){
		numMatches++;
	    matchedBid newMatch;
	    newMatch.matchedTraderOne = buyerBids[buyerMatchId]->getTraderName();
	    newMatch.matchedTraderTwo = sellerBids[seller]->getTraderName();
	    newMatch.clearingPrice = clearBids(&sellerBids[seller], &buyerBids[buyerMatchId]);

	    addMatchToMatchedBids(&newMatch);
	    removeBids(buyerMatchId, seller);

	    numBuyBids = numBuyBids -1;
	    numSellBids = numSellBids -1;
	    }
	    foundBuyer = false;
	}
    }
}

double auctioneer::clearBids(bid **seller, bid **buyer){
    return (double) (((*buyer)->getBidPrice())+((*seller)->getBidPrice()))/2;
   
}

int auctioneer::getNumMatches(){
    return numMatches;
}

matchedBid * auctioneer::distributeMatches(){
    return matches;
}

void auctioneer::addMatchToMatchedBids(matchedBid *newMatch){
    matchedBid *tempMatchedBids = new matchedBid[numMatches];

    for(int i = numMatches; i >= 0; i--){
	tempMatchedBids[i-1] = matches[i-1];
    }

    delete[] matches;
    *matches = *tempMatchedBids;

    matches[numMatches] = *newMatch;
}

void auctioneer::removeBids(int removeBuyerNum, int removeSellerNum){
    bid *tempBuy = new bid[numBuyBids-1];
    bid *tempSell = new bid[numSellBids-1];

    for(int i = numBuyBids-1; i >= 0; i--){
	if(i != removeBuyerNum){
	    tempBuy[i] = *buyerBids[i];
	}
    }

    delete[] &buyerBids;
    *buyerBids = tempBuy;

    for(int i = numSellBids-1; i >= 0; i--){
	if(i != removeSellerNum){
	    tempSell[i] = *sellerBids[i];
	}
    }

    delete [] &sellerBids;

    *sellerBids = tempSell;

    numBuyBids = numBuyBids - 1;
    numSellBids = numSellBids - 1;
} 

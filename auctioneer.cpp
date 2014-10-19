#include "auctioneer.h"
#include "bid.h"
#include "match.h"

#include <iostream>

using namespace std;

auctioneer::auctioneer(){
}

auctioneer::~auctioneer(){
}

void auctioneer::getBid(bid Bid){
    if(Bid.getBidType() == 'A'){
	Bid.setBidId(sellerBids.size()+1);
	sellerBids.push_back(Bid);
    }
    if(Bid.getBidType() == 'B'){
	Bid.setBidId(sellerBids.size()+1);
	buyerBids.push_back(Bid);
    }

}

void auctioneer::announceBids(){
    cout << "Buyer Bids Received\n";
    for(int i = buyerBids.size()-1; i>=0; i--){
	cout << "Name: " << buyerBids[i].getTraderName() << endl
	     << "Price: " << buyerBids[i].getBidPrice() << endl
	     << endl;
    }

    cout << "Seller Bids Received\n";
    for(int i = sellerBids.size()-1; i>=0; i--){
	cout << "Name: " << sellerBids[i].getTraderName() << endl
	     << "Price: " << sellerBids[i].getBidPrice() << endl
	     << endl;
    }
}

void auctioneer::announceMatches(){
    cout << "Matches Found\n";
    for(int i = matches.size()-1; i>=0; i--){
	cout << "Buyer Name: " << matches[i].buyerName << endl
	     << "Seller Name: " << matches[i].sellerName << endl
	     << "Clearing Price: " << matches[i].clearingPrice << endl
	     << endl;
    }
}

void auctioneer::matchBids(){
    int buyerMatchId = NUMBUYER;
    bool foundBuyer = false;

    //find the buyer with the highest price for each seller
    for(int seller = numSellBids; seller >= 0; seller--){
	for(int buyer = numBuyBids; buyer >= 0; buyer--){
	    if(sellerBids[seller].getBidPrice() <= buyerBids[buyer].getBidPrice()){
		if(buyerBids[buyer].getBidPrice() > buyerBids[buyerMatchId].getBidPrice()){
		    buyerMatchId = buyer;
		    foundBuyer = true;
		}
	    }

	    //for each buyer found add to matches
	    if(foundBuyer){
		numMatches++;

		//create the match structure and fill with infomation
		matchedBid newMatch;
		newMatch.buyerName = buyerBids[buyerMatchId].getTraderName();
		newMatch.sellerName = sellerBids[seller].getTraderName();
		newMatch.clearingPrice = clearBids(&sellerBids[seller], &buyerBids[buyerMatchId]);

		matches.push_back(newMatch);

		//remove the found matches from appropriate vecter
		buyerBids.erase(buyerBids.begin() + buyerMatchId);
		sellerBids.erase(sellerBids.begin() + seller);

		numBuyBids = numBuyBids - 1;
		numSellBids = numSellBids - 1;
	    }
	    foundBuyer = false;
	}
    }
}

double auctioneer::clearBids(bid *seller, bid *buyer){
    return (double) ((buyer->getBidPrice())+(seller->getBidPrice()))/2;
   
}

int auctioneer::getNumMatches(){
    return numMatches;
}

std::vector<matchedBid> auctioneer::distributeMatches(){
    return matches;
}




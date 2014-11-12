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
	numBuyBids++;
	cout << "Num Buy Buds: " << numBuyBids << endl;
	
    }
    if(Bid.getBidType() == 'B'){
	Bid.setBidId(sellerBids.size()+1);
	buyerBids.push_back(Bid);
	numSellBids++;
	cout << "num sell bids: " << numSellBids << endl;
    }

}

void auctioneer::matchBids(){
    int buyerMatchId = buyerBids.size()-1;
    bool foundBuyer = false;
    bool matchedAllPossible = false;

    while(matchedAllPossible == false){
	matchedAllPossible = true;
	//find the buyer with the highest price for each seller
	for(int seller = sellerBids.size()-1; seller >= 0; seller--){
	    for(int buyer = buyerBids.size()-1; buyer >= 0; buyer--){
		
		if(sellerBids[seller].getItemName().compare(buyerBids[buyer].getItemName())){
		    if(sellerBids[seller].getBidPrice() <= buyerBids[buyer].getBidPrice()){
			if(buyerBids[buyer].getBidQuantity() <= sellerBids[seller].getBidQuantity()){
			    if(buyerBids[buyer].getBidPrice() > buyerBids[buyerMatchId].getBidPrice()){
				buyerMatchId = buyer;
				matchedAllPossible = false;
				foundBuyer = true;
			    }
			}
		    }
		}
		
		//for each buyer found add to matches
		if(foundBuyer){
		    numMatches++;

		    //create the match structure and fill with infomation
		    matchedBid newMatch;
		    newMatch.bidId = sellerBids[seller].getBidId();
		    newMatch.buyerName = buyerBids[buyerMatchId].getTraderName();
		    newMatch.sellerName = sellerBids[seller].getTraderName();
		    newMatch.clearingPrice = clearBids(&sellerBids[seller], &buyerBids[buyerMatchId]);
		    newMatch.quantity = buyerBids[buyerMatchId].getBidQuantity();
		    newMatch.matchId = numMatches;
		    newMatch.itemName = sellerBids[seller].getItemName();

		    matches.push_back(newMatch);

		    //Add match to escrow
		    createEscrowAccount(newMatch.matchId, newMatch.sellerName, newMatch.buyerName);
		    
		    //remove quantity from both bidder and seller
		    sellerBids[seller].setBidQuantity(sellerBids[seller].getBidQuantity()-buyerBids[buyerMatchId].getBidQuantity());
		    buyerBids[buyerMatchId].setBidQuantity(0);
		    //remove the found matches from appropriate vecter if empty of all quantity
		    if(buyerBids[buyerMatchId].getBidQuantity() < 1){
			buyerBids.erase(buyerBids.begin() + buyerMatchId);
			numBuyBids--;
		    }
		    if(sellerBids[seller].getBidQuantity() < 1){
			sellerBids.erase(sellerBids.begin() + seller);
			numSellBids--;

		    }
		    foundBuyer = false;
		}
	    }
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

void auctioneer::createEscrowAccount(int matchId, std::string sellerName, std::string buyerName){
    escrow newEscrow;
    newEscrow.matchId = matchId;
    newEscrow.receivingTrader = sellerName;
    newEscrow.payingTrader = buyerName;
    escrowVector.push_back(newEscrow);
}

void auctioneer::addMoneyToEscrow(int matchId, int money){
    for(int i = escrowVector.size()-1; i >=0; i--){
	if(escrowVector[i].matchId == matchId){
	    escrowVector[i].money = money;
	}
    }
}

double auctioneer::removeMoneyFromEscrow(int matchId, std::string){
    for(int i = escrowVector.size()-1; i>=0; i--){
	if(escrowVector[i].matchId == matchId){
	    double moneyToReturn = escrowVector[i].money;
	    escrowVector.erase(escrowVector.begin() + i);
	    return moneyToReturn;
	}
    }
    return -1;
}


std::vector<bid> auctioneer::getBuyerBids(){
    return buyerBids;
}

std::vector<bid> auctioneer::getSellerBids(){
    return sellerBids;
}

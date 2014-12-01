#include "auctioneer.h"
#include "bid.h"
#include "match.h"

#include <iostream>

auctioneer::auctioneer(){
}

auctioneer::~auctioneer(){
}

void auctioneer::getBid(bid Bid){
    bool bidItemExists = false;
    numBids++;
    for(int i = bidItem.size()-1; i>=0; i--){
	
	if(Bid.getItemNo() == bidItem[i]->item){
	    if(Bid.getBidType() == 'A'){
		Bid.setBidId(numBids);
		bidItem[i]->sellerBids.push_back(Bid);
	    }
	    if(Bid.getBidType() == 'B'){
		Bid.setBidId(numBids);
		bidItem[i]->buyerBids.push_back(Bid);
	    }
	    bidItemExists = true;
	}
    }
    if(!bidItemExists){
	std::unique_ptr<buyerAndSellerBids> newItemType(new buyerAndSellerBids(Bid.getItemNo()));
	bidItem.push_back(std::move(newItemType));

	if(Bid.getBidType() == 'A'){
	    Bid.setBidId(numBids);
	    bidItem[bidItem.size()-1]->sellerBids.push_back(Bid);
	}
	if(Bid.getBidType() == 'B'){
	    Bid.setBidId(numBids);
	    bidItem[bidItem.size()-1]->buyerBids.push_back(Bid);
	}
    }
}
   
    

void auctioneer::matchBids(){
    for(int i = bidItem.size()-1; i >= 0; i--){
	int buyerMatchId = bidItem[i]->buyerBids.size()-1;
	bool foundBuyer = false;
	bool matchedAllPossible = false;

	while(matchedAllPossible == false){
	    matchedAllPossible = true;
	    //find the buyer with the highest price for each seller
	    for(int seller = bidItem[i]->sellerBids.size()-1; seller >= 0; seller--){
		for(int buyer = bidItem[i]->buyerBids.size()-1; buyer >= 0; buyer--){

		    if(bidItem[i]->sellerBids[seller].getBidPrice() <= bidItem[i]->buyerBids[buyer].getBidPrice()){
			//if buyer wants less or equal to number avaliable continue
			if(bidItem[i]->buyerBids[buyer].getBidQuantity() <= bidItem[i]->sellerBids[seller].getBidQuantity()){
			    if(bidItem[i]->buyerBids[buyer].getBidPrice() > bidItem[i]->buyerBids[buyerMatchId].getBidPrice()){
				buyerMatchId = buyer;
				matchedAllPossible = false;
				foundBuyer = true;
			    }
			}
		    }
		}
		//for each buyer found add to matches
		//runs after we have finished the buyer for loop
		if(foundBuyer){

		    //create the match structure and fill with infomation
		    matchedBid newMatch;
		    newMatch.bidId = bidItem[i]->sellerBids[seller].getBidId();
		    newMatch.buyerName = bidItem[i]->buyerBids[buyerMatchId].getTraderName();
		    newMatch.sellerName = bidItem[i]->sellerBids[seller].getTraderName();
		    newMatch.clearingPrice = clearBids(&bidItem[i]->sellerBids[seller], &bidItem[i]->buyerBids[buyerMatchId]);
		    newMatch.quantity = bidItem[i]->buyerBids[buyerMatchId].getBidQuantity();
		    newMatch.matchId = matches.size();
		    newMatch.itemNo = bidItem[i]->sellerBids[seller].getItemNo();

		    matches.push_back(newMatch);

		    //Add match to escrow
		    createEscrowAccount(newMatch.matchId, newMatch.sellerName, newMatch.buyerName);
		    
		    //remove quantity from both bidder and seller
		    bidItem[i]->sellerBids[seller].setBidQuantity(bidItem[i]->sellerBids[seller].getBidQuantity() - bidItem[i]->buyerBids[buyerMatchId].getBidQuantity());
		    bidItem[i]->buyerBids[buyerMatchId].setBidQuantity(0);
		    //remove the found matches from appropriate vecter if empty of all quantity
		    if(bidItem[i]->buyerBids[buyerMatchId].getBidQuantity() < 1){
			bidItem[i]->buyerBids.erase(bidItem[i]->buyerBids.begin() + buyerMatchId);
		    }
		    if(bidItem[i]->sellerBids[seller].getBidQuantity() < 1){
			bidItem[i]->sellerBids.erase(bidItem[i]->sellerBids.begin() + seller);

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
    std::vector<bid> bidsToReturn;
    for(int i = bidItem.size()-1; i >=0 ; i--){
	for(int j = bidItem[i]->buyerBids.size()-1; j>=0; j--){
	    bidsToReturn.push_back(bidItem[i]->buyerBids[j]);
	}
    }
    return bidsToReturn;
}

std::vector<bid> auctioneer::getSellerBids(){
    std::vector<bid> bidsToReturn;
    for(int i = bidItem.size()-1; i >=0 ; i--){
	for(int j = bidItem[i]->sellerBids.size()-1; j>=0; j--){
	    bidsToReturn.push_back(bidItem[i]->sellerBids[j]);
	}
    }
    return bidsToReturn;
}

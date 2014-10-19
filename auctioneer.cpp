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
    //find width of collumn
    // 19 is how many characters are in "Buyer Bids received" the set smallest width
    int width = 19;
    for(int i = buyerBids.size()-1; i>=0; i--){
	if((buyerBids[i].getTraderName().size() + 6) > width){
	    width = buyerBids[i].getTraderName().size() + 6;
	}
    }
    //Add space for readability
    width++;

    cout << "Buyer Bids Received";
    int currentPlace = 19;
    //pad till edge of collumn
    while(currentPlace < width){
	cout << " ";
	currentPlace++;
    }
    currentPlace = 0;
    cout << "| ";
    cout << "Seller Bids Received\n";

    for(currentPlace = 0; currentPlace < width; currentPlace++){
	cout << "-";
    }
    cout << "+";

    int tempWidth = 20;
    for(int i = sellerBids.size()-1; i>=0; i--){
	if((sellerBids[i].getTraderName().size() + 6) > tempWidth){
	    tempWidth = sellerBids[i].getTraderName().size() + 6;
	}
    }    
    currentPlace = 0;
    for(currentPlace = 0; currentPlace < tempWidth; currentPlace++){
	cout << "-";
    }
    cout << endl;
    currentPlace = 0;

    for(int buyersLeftToPrint = buyerBids.size()-1, sellersLeftToPrint = sellerBids.size()-1;
	buyersLeftToPrint >=0 || sellersLeftToPrint >=0;
	buyersLeftToPrint--, sellersLeftToPrint--){
	int nameLength = 6;
	int priceLength = 7;
	//check we have buyers and sellers left to print before we continue
	if(buyersLeftToPrint > -1){
	    currentPlace = nameLength + buyerBids[buyersLeftToPrint].getTraderName().size();
	    cout << "Name: " << buyerBids[buyersLeftToPrint].getTraderName();
	}
	while(currentPlace < width){
	    cout << " ";
	    currentPlace++;
	}
	cout << "| ";
	if(sellersLeftToPrint > -1){
	    cout << "Name: " << sellerBids[sellersLeftToPrint].getTraderName();
	}
	cout << endl;
	currentPlace = 0;
	//way of counting digets coutursy Vatali on stack overflow simply divide by ten till we cant any more
	if(buyersLeftToPrint > -1){
	    int number = buyerBids[buyersLeftToPrint].getBidPrice();
	    while (number) {
		number /= 10;
		currentPlace++;
	    }
	    currentPlace = currentPlace + priceLength;
	    cout << "Price: " << buyerBids[buyersLeftToPrint].getBidPrice();
	}
	while(currentPlace < width){
	    cout << " ";
	    currentPlace++;
	}
	cout << "| ";
	if(sellersLeftToPrint > -1){
	    cout << "Price: " << sellerBids[sellersLeftToPrint].getBidPrice();
	} 
	cout << endl;
	int i = 0;
	while(i < width){
	    cout << " ";
	    i++;
	}
	cout << "|" << endl;

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




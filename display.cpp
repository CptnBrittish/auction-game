#include "display.h"
#include "match.h"
#include "bid.h"
#include "item.h"

#include <vector>
#include <iostream>

void showBids(std::vector<bid> buyerBids, std::vector<bid> sellerBids){
    //find width of collumn
    // 19 is how many characters are in "Buyer Bids received" the set smallest width
    unsigned int width = 19;
    for(int i = buyerBids.size()-1; i>=0; i--){
	if((buyerBids[i].getTraderName().size() + 6) > width){
	    width = buyerBids[i].getTraderName().size() + 6;
	}
    }
    //Add space for readability
    width++;

    std::cout << "Buyer Bids Received";
    unsigned int currentPlace = 19;
    //pad till edge of collumn
    fillToEndOfCollumn(currentPlace, width);
    currentPlace = 0;
    std::cout << "| ";
    std::cout << "Seller Bids Received\n";

    for(currentPlace = 0; currentPlace < width; currentPlace++){
	std::cout << "-";
    }
    std::cout << "+";

    unsigned int tempWidth = 20;
    for(int i = sellerBids.size()-1; i>=0; i--){
	if((sellerBids[i].getTraderName().size() + 6) > tempWidth){
	    tempWidth = sellerBids[i].getTraderName().size() + 6;
	}
    }    
    currentPlace = 0;
    for(currentPlace = 0; currentPlace < tempWidth; currentPlace++){
	std::cout << "-";
    }
    std::cout << std::endl;
    currentPlace = 0;

    for(int buyersLeftToPrint = buyerBids.size()-1, sellersLeftToPrint = sellerBids.size()-1;
	buyersLeftToPrint >=0 || sellersLeftToPrint >=0;
	buyersLeftToPrint--, sellersLeftToPrint--){
	
	int nameLength = 6;
	int priceLength = 7;
	int quantityLength = 10;
	int itemLength = 6;
	
	//check we have buyers and sellers left to print before we continue
	if(buyersLeftToPrint > -1){
	    currentPlace = nameLength + buyerBids[buyersLeftToPrint].getTraderName().size();
	    std::cout << "Name: " << buyerBids[buyersLeftToPrint].getTraderName();
	}
	fillToEndOfCollumn(currentPlace, width);
	std::cout << "| ";
	if(sellersLeftToPrint > -1){
	    std::cout << "Name: " << sellerBids[sellersLeftToPrint].getTraderName();
	}
	std::cout << std::endl;
	currentPlace = 0;
    
    
	if(buyersLeftToPrint > -1){
	    currentPlace = getItemName(buyerBids[buyersLeftToPrint].getItemNo()).size() + itemLength;
	    std::cout << "Item: " << getItemName(buyerBids[buyersLeftToPrint].getItemNo());
	}
	
	fillToEndOfCollumn(currentPlace, width);
	
	std::cout << "| ";
	if(sellersLeftToPrint > -1){
	    std::cout << "Item: " << getItemName(sellerBids[sellersLeftToPrint].getItemNo());
	}
	std::cout << std::endl;
	
	currentPlace = 0;
	
	if(buyersLeftToPrint > -1){
	    currentPlace = findCharacterLengthOfInt(buyerBids[buyersLeftToPrint].getBidPrice()) + priceLength;

	    std::cout << "Price: " << buyerBids[buyersLeftToPrint].getBidPrice();
	}
	fillToEndOfCollumn(currentPlace, width);
	std::cout << "| ";
	if(sellersLeftToPrint > -1){
	    std::cout << "Price: " << sellerBids[sellersLeftToPrint].getBidPrice();
	}
	std::cout << std::endl;
	
	currentPlace = 0;

	if(buyersLeftToPrint > -1){
	    currentPlace = findCharacterLengthOfInt(buyerBids[buyersLeftToPrint].getBidQuantity()) + quantityLength;
	    std::cout << "Quantity: " << buyerBids[buyersLeftToPrint].getBidQuantity();
	}
	
        fillToEndOfCollumn(currentPlace, width);
	
	std::cout << "| ";
	if(sellersLeftToPrint > -1){
	    std::cout << "Quantity: " << sellerBids[sellersLeftToPrint].getBidQuantity();
	} 
	std::cout << std::endl;
	
	currentPlace  = 0;
	
	fillToEndOfCollumn(currentPlace, width);
	
	std::cout << "|" << std::endl;

    }

}

void fillToEndOfCollumn(int startPlace, int endPlace){
	while(startPlace < endPlace){
	    std::cout << " ";
	    startPlace++;
	} 
}

int findCharacterLengthOfInt(int i){
    int length;
    while (i) {
	i /= 10;
	length++;
    }
    return length;
}

void showMatches(std::vector<matchedBid> matches){
    if(matches.size() > 0){
	std::cout << "Matches Found\n";
	for(int i = matches.size()-1; i>=0; i--){
	    std::cout << "Buyer Name: " << matches[i].buyerName << std::endl
		      << "Seller Name: " << matches[i].sellerName << std::endl
		      << "Clearing Price: " << matches[i].clearingPrice << std::endl
		      << std::endl;
	}
    } else {
	std::cout << "No matches found" << std::endl;
    }
}

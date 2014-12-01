#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "match.h"
#include "bid.h"
#include "limits.h"
#include "escrow.h"

#include <vector>
#include <memory>

    class buyerAndSellerBids {
    public:
	std::vector<bid> buyerBids;
	std::vector<bid> sellerBids;
	int item;
	buyerAndSellerBids(int itemNum){item = itemNum;};
    };

class auctioneer {
private:

    int numBids = 0;
    
    std::vector<std::unique_ptr<buyerAndSellerBids>> bidItem; 

    std::vector<matchedBid> matches;

    std::vector<escrow> escrowVector;
    
public:
    auctioneer();
    ~auctioneer();

    void announceBids();
    void announceMatches();
    void getBid(bid);
    void matchBids();
    double clearBids(bid*, bid*);
    std::vector<matchedBid> distributeMatches();

    void createEscrowAccount(int, std::string, std::string);
    void addMoneyToEscrow(int, int);
    double removeMoneyFromEscrow(int, std::string);

    std::vector<bid> getBuyerBids();
    std::vector<bid> getSellerBids();
};

#endif

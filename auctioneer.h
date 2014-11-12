#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "match.h"
#include "bid.h"
#include "limits.h"
#include "escrow.h"

#include <vector>

class auctioneer {
private:
    int numBuyBids = 0;
    int numSellBids = 0;
    std::vector<bid> buyerBids;
    std::vector<bid> sellerBids;

    std::vector<matchedBid> matches;
    int numMatches = 0;

    std::vector<escrow> escrowVector;
public:
    auctioneer();
    ~auctioneer();

    int getNumMatches();
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

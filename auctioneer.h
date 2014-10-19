#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "matchStructs.h"
#include "bid.h"
#include "limits.h"

#include <vector>

class auctioneer {
private:
    int numBuyBids = NUMBUYER;
    int numSellBids = NUMSELLER;
    std::vector<bid> buyerBids;
    std::vector<bid> sellerBids;

    std::vector<matchedBid> matches;
    int numMatches = 0;

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
};

#endif

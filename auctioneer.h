#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "matchStructs.h"
#include "bid.h"
#include "limits.h"

class auctioneer {
private:
    int numBuyBids = NUMBUYER;
    int numSellBids = NUMSELLER;
    bid *buyerBids[NUMBUYER];
    bid *sellerBids[NUMSELLER];

    matchedBid *matches;
    int numMatches = 0;

public:
    auctioneer();
    ~auctioneer();

    int getNumMatches();
    void getBid(bid*);
    void matchBids();
    double clearBids(bid**, bid**);
    void removeBids(int, int);
    void addMatchToMatchedBids(matchedBid*);
    matchedBid * distributeMatches();
};

#endif

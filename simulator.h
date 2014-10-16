#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "trader.h"
#include "auctioneer.h"
#include "bid.h"
#include "limits.h"
#include "matchStructs.h"

class simulator {
private:
    static const int NUMTRADERS = NUMBUYER + NUMSELLER;
    trader * Traders[NUMTRADERS];
    auctioneer auctionMaster;
    bid * Bid[NUMTRADERS];

public:
    simulator();
    ~simulator();

    void collectBids();
    void distributeBids();
    void getAndDistributeMatches();
};

#endif

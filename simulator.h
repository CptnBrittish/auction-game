#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "trader.h"
#include "auctioneer.h"
#include "bid.h"
#include "limits.h"
#include "match.h"

#include <vector>

class simulator {
private:
    static const int NUMTRADERS = NUMBUYER + NUMSELLER;
    std::vector<trader> Traders;
    auctioneer auctionMaster;
    std::vector<bid> Bid;
 

public:
    simulator();
    ~simulator();

    void collectBids();
    void distributeBids();
    void getAndDistributeMatches();
};

#endif

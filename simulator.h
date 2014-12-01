#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "trader.h"
#include "auctioneer.h"
#include "bid.h"
#include "limits.h"
#include "match.h"
#include "player.h"

#include <memory>
#include <vector>
#include <string>

class simulator {
private:
    static const int NUMTRADERS = NUMBUYER + NUMSELLER;
    std::vector<trader> Traders;
    player Player;
    auctioneer auctionMaster;
    std::vector<bid> Bid;
    std::vector<matchedBid> matchedBids;
    std::string getTraderName(std::vector<std::string>&, std::vector<std::string>&);
 

public:
    simulator();
    ~simulator();

    void runSimulator();
    void collectBids();
    void distributeBids();
    void getAndDistributeMatches();
    void distributeEscrowMoney();
    void getEscrowMoney();
};

#endif

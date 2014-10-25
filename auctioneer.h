#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "match.h"
#include "bid.h"
#include "limits.h"
#include "escrow.h"

#include <vector>

class auctioneer {
private:
    int numBuyBids = NUMBUYER;
    int numSellBids = NUMSELLER;
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
    int removeMoneyFromEscrow(int, std::string);
};

#endif

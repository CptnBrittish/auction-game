#ifndef TRADER_H
#define TRADER_H

#include <string>
#include "bid.h"
#include "matchStructs.h"

class trader {
private:
    std::string traderName;
    char traderType;
    bid *traderBid = new bid;
    matchedBid match;

public:
    trader();
    trader(const char*, char);
    ~trader();

    std::string getName();

    bid * generateBid();

    void getMatchedBid(matchedBid*);
};

#endif

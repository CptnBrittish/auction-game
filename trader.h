#ifndef TRADER_H
#define TRADER_H

#include <string>
#include "bid.h"
#include "match.h"

class trader {
private:
    std::string traderName;
    char traderType;
    bid traderBid;
    matchedBid match;

public:
    trader();
    trader(const char*, char);
    trader(std::string, char);
    ~trader();

    std::string getName();
    char getType();

    bid generateBid();

    void getMatchedBid(matchedBid);
};

#endif

#ifndef TRADER_H
#define TRADER_H

#include "bid.h"
#include "match.h"

#include <string>
#include <vector>

class trader {
private:
std::string traderName;
char traderType;
std::vector<bid> traderBids;
matchedBid match;

public:
trader();
trader(const char*, char);
trader(std::string, char);
~trader();

std::string getName();
char getType();

std::vector<bid> generateBid();

void getMatchedBid(matchedBid);
};

#endif

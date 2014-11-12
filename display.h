#ifndef DISPLAY_H
#define DISPLAY_H

#include "match.h"
#include "bid.h"

#include <vector>

void showMatches(std::vector<matchedBid>);
void showBids(std::vector<bid>, std::vector<bid>);
void fillToEndOfCollumn(int, int);
int findCharacterLengthOfInt(int);

#endif

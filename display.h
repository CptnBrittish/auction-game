#ifndef DISPLAY_H
#define DISPLAY_H

#include "match.h"
#include "bid.h"
#include "item.h"

#include <vector>
class display{
private:
    items *itemTypes;

    void fillToEndOfCollumn(int, int);
    int findCharacterLengthOfInt(int);

public:
    void showMatches(std::vector<matchedBid>);
    void showBids(std::vector<bid>, std::vector<bid>);

    display(items*);
    display(){};
};
#endif

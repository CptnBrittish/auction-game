#ifndef PLAYER_H
#define PLAYER_H

#include "trader.h"
#include "bid.h"
#include "match.h"
#include "inventory.h"

#include <string>
#include <vector>

class player : public trader {

public:
    player();
    
    std::vector<bid> generateBid();
};

#endif

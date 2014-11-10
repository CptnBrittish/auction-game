#ifndef ESCROW_H
#define ESCROW_H

#include "inventory.h"

#include <string>

struct escrow {
    int matchId;
    int money;
    std::string receivingTrader;
    std::string payingTrader;
    item escrowedItem;
    
};

#endif

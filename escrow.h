#ifndef ESCROW_H
#define ESCROW_H

#include <string>

struct escrow {
    int matchId;
    int money;
    std::string receivingTrader;
    std::string payingTrader;
};

#endif

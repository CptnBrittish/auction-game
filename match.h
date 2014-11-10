#ifndef MATCHSTRUCTS_H
#define MATCHSTRUCTS_H

#include <string>

struct matchedBid {
    int bidId;
    int matchId;
    std::string sellerName;
    std::string buyerName;
    std::string itemName;
    int quantity;
    double clearingPrice;
};


#endif

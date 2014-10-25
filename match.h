#ifndef MATCHSTRUCTS_H
#define MATCHSTRUCTS_H

#include <string>

struct matchedBid {
    int bidId;
    std::string sellerName;
    std::string buyerName;
    int quantity;
    double clearingPrice;
};


#endif

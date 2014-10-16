#ifndef BID_H
#define BID_H

#include <string>

class bid {
private:
    std::string traderName;
    int bidId;
    char bidType;
    double bidPrice;

public:
    std::string getTraderName();
    void setTraderName(std::string);

    int getBidId();
    void setBidId(int);

    char getBidType();
    void setBidType(char);

    double getBidPrice();
    void setBidPrice(double);

    bid();
    ~bid();
};

#endif

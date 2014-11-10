#ifndef BID_H
#define BID_H

#include <string>

class bid {
private:
    std::string traderName;
    int bidId;
    int bidQuantity;
    /*
     * A = seller
     * B = buyer
     */
    char bidType;
    double bidPrice;
    std::string itemName;

public:
    std::string getTraderName();
    void setTraderName(std::string);
    void setTraderName(const char *);

    int getBidId();
    void setBidId(int);

    int getBidQuantity();
    void setBidQuantity(int);

    char getBidType();
    void setBidType(char);

    double getBidPrice();
    void setBidPrice(double);

    std::string getItemName();
    void setItemName(std::string);

    bid();
    bid(const bid&);
    bid& operator=(const bid&);
    ~bid();
};

#endif

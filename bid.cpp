#include "bid.h"

#include <string>

using namespace std;

bid::bid(){
    bidId = 0;
    bidQuantity = 0;
    bidPrice = 0.0;
}

bid::bid(const bid& other){
    traderName = string(other.traderName);
    bidId = other.bidId;
    bidQuantity = other.bidQuantity;
    bidType = other.bidType;
    bidPrice = other.bidPrice;
    itemNo = other.itemNo;
}

bid& bid::operator=(const bid& other){
    traderName.assign(other.traderName);
    bidId = other.bidId;
    bidQuantity = other.bidQuantity;
    bidType = other.bidType;
    bidPrice = other.bidPrice;
    itemNo = other.itemNo;
    return *this;
} 

std::string bid::getTraderName(){
    return traderName;
}

void bid::setTraderName(string name){
    traderName.assign(name);
}

void bid::setTraderName(const char * name){
    traderName.assign(string(name));
}

int bid::getBidId(){
    return bidId;
}

void bid::setBidId(int id){
    bidId = id;
}

int bid::getBidQuantity(){
    return bidQuantity;
}

void bid::setBidQuantity(int quantity){
    bidQuantity = quantity;
}

char bid::getBidType(){
    return bidType;
}

void bid::setBidType(char type){
    bidType = type;
}

double bid::getBidPrice(){
    return bidPrice;
}

void bid::setBidPrice(double price){
    bidPrice = price;
}

int bid::getItemNo(){
    return itemNo;
}

void bid::setItemNo(int num){
    itemNo = num;
}

bid::~bid(){
}

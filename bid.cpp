#include "bid.h"

#include <string>

using namespace std;

bid::bid(){
    bidId = 0;
    bidPrice = 0.0;
}

std::string bid::getTraderName(){
    return traderName;
}

void bid::setTraderName(string name){
    traderName = name;
}

int bid::getBidId(){
    return bidId;
}

void bid::setBidId(int id){
    bidId = id;
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

bid::~bid(){
}

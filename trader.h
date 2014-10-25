#ifndef TRADER_H
#define TRADER_H

#include "bid.h"
#include "match.h"

#include <string>
#include <vector>

class trader {
private:
std::string traderName;
char traderType;
double money;
double moneyLeftForBids;

std::vector<bid> traderBids;


public:
trader();
trader(const char*, char);
trader(std::string, char);
~trader();

std::string getName();
char getType();
double getTraderMoney();
void setTraderMoney();

std::vector<bid> generateBid();
std::vector<matchedBid> matchedBids;

void getMatchedBid(matchedBid);

int sendMoneyToEscrow(int);
void getMoneyFromEscrow(int, int);
};

#endif

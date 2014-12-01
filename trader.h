#ifndef TRADER_H
#define TRADER_H

#include "bid.h"
#include "match.h"
#include "inventory.h"

#include <string>
#include <vector>

class trader {
private:
std::string traderName;
/*
 * A = seller
 * B = buyer
 */
char traderType;
double money;
double moneyLeftForBids;

std::vector<matchedBid> matchedBids;
std::vector<item> inventory;
std::vector<bid> traderBids;

void condenseInventory();

public:
trader();
trader(const char*, char);
trader(std::string, char);
~trader();

std::string getName();
void setTraderName(std::string);

char getType();

double getTraderMoney();
void setTraderMoney(double);

void setMoneyLeft(double);
double getMoneyLeft();

std::vector<bid> generateBid();

void getMatchedBid(matchedBid);

int sendMoneyToEscrow(int);
void getMoneyFromEscrow(int, int);
};

#endif

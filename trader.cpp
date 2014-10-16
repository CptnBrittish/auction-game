#include "trader.h"
#include "matchStructs.h"
#include "limits.h"

#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;
 
trader::trader(){
    traderName = "Temporary Name";
    traderType = 'A';
}

trader::trader(const char * name, char type){
    traderName = string(name);
    traderType = type;
}

trader::~trader(){
}

string trader::getName(){
    return traderName;
}

bid * trader::generateBid(){
    srand(time(NULL));
    traderBid->setBidPrice(rand() % (MAXPRICE - MINPRICE) + MINPRICE);

    traderBid->setTraderName(traderName);
    traderBid->setBidType(traderType);

    //We set this anyway but there is no need to the auctionmaster deals with the bidIds after they are handed in
    traderBid->setBidId(0);

    return traderBid;
}

void trader::getMatchedBid(matchedBid* matched){

}

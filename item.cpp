#include "item.h"
#include "itemNames.h"

#include <string>

std::string getItemName(int itemNo){
    return itemNameOptions[itemNo];
}

std::string getItemDescription(int itemNo){
    return itemDescriptionOptions[itemNo];
}

int getItemNum(std::string itemName){
    for(int i = 4; i>=0; i--){
	if(getItemName(i) == itemName){
	    return i;
	}
    }
    return -1;
}

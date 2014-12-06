#include "item.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

items::items(){
    std::ifstream itemTypesFile;
    itemTypesFile.open("items");
    std::string line;
    while(std::getline(itemTypesFile, line)){
	item newItem;
	if(line == ":start"){
	    while(line != ":end"){
		std::getline(itemTypesFile, line);
		if(line == ":name"){
		    std::getline(itemTypesFile, line);
		    newItem.itemName = line;
		}
		if(line == ":description"){
		    std::getline(itemTypesFile, line);
		    newItem.itemDescription = line;
		}
	    }
	}
	itemTypes.push_back(newItem);
    }
    itemTypesFile.close();
}

std::string items::getItemName(int itemNo){
    return itemTypes[itemNo].itemName;
}

std::string items::getItemDescription(int itemNo){
    return itemTypes[itemNo].itemDescription;
}

int items::getItemNum(std::string itemName){
    for(int i = itemTypes.size()-1; i>=0; i--){
	if(getItemName(i) == itemName){
	    return i;
	}
    }
    return -1;
}

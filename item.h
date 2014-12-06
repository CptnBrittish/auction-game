#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

class items {
private:
    struct item {
	std::string itemName;
	std::string itemDescription;
    };
    std::vector<item> itemTypes;
public:
    items();
    std::string getItemName(int);
    std::string getItemDescription(int);

    int getNumItems();
    int getItemNum(std::string);
};
#endif

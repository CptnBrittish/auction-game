/*************************************************************************
Copyright 2014 Thomas Atkinson
This file is part of mkGame.
mkGame is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
mkGame is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with mkGame. If not, see <http://www.gnu.org/licenses/>.
*************************************************************************/

#include "parseInput.h"

#include <cstdlib>
#include <string>

int validateIsANumber(std::string &input){
    char num[10] = {'0','1','2','3','4','5','6','7','8','9'};
    bool isNumber = false;

    for(int i = input.length(); i > 0; i--){
	isNumber = false;
	for(int j = 9; j >= 0; j--){
	    if(input.at(i-1) == num[j]){
		isNumber = true;
	    }
	}
	if(isNumber == false){
	    return -1;
	}
    }
    int number = atoi(input.c_str());
    return number;
}

double validateIsADouble(std::string &input){
    char num[11] = {'0','1','2','3','4','5','6','7','8','9','.'};
    bool isNumber = false;

    for(int i = input.length(); i > 0; i--){
	isNumber = false;
	for(int j = 10; j >= 0; j--){
	    if(input.at(i-1) == num[j]){
		isNumber = true;
	    }
	}
	if(isNumber == false){
	    return -1;
	}
    }
    int number = atof(input.c_str());
    return number;
}

std::string validateIsAString(std::string &input){
    char num[10] = {'0','1','2','3','4','5','6','7','8','9'};
    bool isNumber = false;

    for(int i = input.length(); i > 0; i--){
	isNumber = false;
	for(int j = 9; j >= 0; j--){
	    if(input.at(i-1) == num[j]){
		isNumber = true;
	    }
	}
	if(isNumber == true){
	    return "-1";
	}
    }
    return input;
}

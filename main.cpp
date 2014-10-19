#include "simulator.h"

#include <cstdlib>
#include <time.h>

int main(){
    simulator Simulator;
    srand(time(NULL));
    Simulator.collectBids();
    Simulator.distributeBids();
    Simulator.getAndDistributeMatches();
}

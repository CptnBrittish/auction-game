#include "simulator.h"

int main(){
    simulator Simulator;
    Simulator.collectBids();
    Simulator.distributeBids();
    Simulator.getAndDistributeMatches();
}

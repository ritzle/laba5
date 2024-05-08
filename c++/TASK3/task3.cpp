#include "hTask3.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
    vector<trainInfo> trains;
    vector<townInfo> towns;

    creatTrain(trains, towns);
    creatTrain(trains, towns);

    trainsForTown("N", towns);

    cout << endl;
    cout << endl;

    townsForTrain("tr1", trains, towns);
    cout << endl;
    coutTrains(trains);
}
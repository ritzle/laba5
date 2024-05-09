#include "hTask3.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{

    char action;
    string town;
    string train;

    cout << "1 = Create_train 2 = Trains_for_Town 3 = Towns_for_train 4 = trains E = exit" << endl;

    vector<trainInfo> trains;
    vector<townInfo> towns;

    while (true)
    {
        cout << endl;
        cout << "Enter action: ";
        cin >> action;
        switch (action)
        {
        case '1':
            creatTrain(trains, towns);
            break;

        case '2':
            cout << "Enter town: ";
            cin >> town;
            trainsForTown(town, towns);
            break;

        case '3':
            cout << "Enter train: ";
            cin >> train;
            townsForTrain(train, trains, towns);
            break;

        case '4':
            coutTrains(trains);
            break;

        case 'E':
            return 0;
        default:
            cout << "unknown team\n";
        }
    }
}
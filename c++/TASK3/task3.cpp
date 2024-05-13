#include "hTask3.h"

#include <iostream>
#include <string>
#include <map>
#include <deque>

using namespace std;

enum plane
{ // перечислимый тип, ввод с консоли числа
    CREATE_TRAIN = 1,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    EXIT
};

int main()
{

    char action;
    string town;
    string train;

    cout << "1 = Create_train 2 = Trains_for_Town 3 = Towns_for_train 4 = trains E = exit" << endl;

    deque<trainInfo> trains;
    deque<townInfo> towns;

    while (true)
    {
        cout << endl;
        cout << "Enter action: ";
        int command;
        cin >> command;

        if (command == plane::CREATE_TRAIN)
        {
            creatTrain(trains, towns);
        }
        else if (command == plane::TRAINS_FOR_TOWN)
        {
            cout << "Enter town: ";
            cin >> town;
            trainsForTown(town, towns);
        }
        else if (command == plane::TOWNS_FOR_TRAIN)
        {
            cout << "Enter train: ";
            cin >> train;
            townsForTrain(train, trains, towns);
        }
        else if (command == plane::TRAINS)
        {
            coutTrains(trains);
        }
        else if (command == plane::EXIT)
        {
            return 0;
        }
    }
}
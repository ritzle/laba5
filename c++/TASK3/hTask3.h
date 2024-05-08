#ifndef HTASK3_H
#define HTASK3_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

struct trainInfo
{
    string name;
    vector<string> stationTown;
};

struct townInfo
{
    string name;
    vector<string> passingTrain;
};

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &nums) // возвращаем ссылку на поток что бы cout мог ухватиться и вывести что-то следом
{
    for (auto i : nums)
    {
        os << i << " ";
    }
    return os;
}

void creatTrain(vector<trainInfo> &trains, vector<townInfo> &towns);
void trainsForTown(std::string town, vector<townInfo> &towns); // вывод всех поездов которые проходят черз город

void townsForTrain(std::string nameTrain, vector<trainInfo> &train, vector<townInfo> &towns);
void trainsForTownDop(std::string town, std::string train, vector<townInfo> &towns);
void coutTrains(vector<trainInfo> &trains);

void creatTown(string train, string town, vector<townInfo> &towns);

#endif // HTASK3_H

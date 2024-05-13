#ifndef HTASK3_H
#define HTASK3_H

#include <iostream>
#include <string>
#include <deque>
#include <sstream>
#include <limits>
#include <algorithm>
#include <deque>

using namespace std;

struct trainInfo
{
    string name;
    deque<string> stationTown;
};

struct townInfo
{
    string name;
    deque<string> passingTrain;
};

template <typename T>
ostream &operator<<(ostream &os, const deque<T> &nums) // возвращаем ссылку на поток что бы cout мог ухватиться и вывести что-то следом
{
    for (auto i : nums)
    {
        os << i << " ";
    }
    return os;
}

void creatTrain(deque<trainInfo> &trains, deque<townInfo> &towns);
void trainsForTown(std::string town, deque<townInfo> &towns); // вывод всех поездов которые проходят черз город

void townsForTrain(std::string nameTrain, deque<trainInfo> &train, deque<townInfo> &towns);
void trainsForTownDop(std::string town, std::string train, deque<townInfo> &towns);
void coutTrains(const std::deque<trainInfo> &trains);

void creatTown(string train, string town, deque<townInfo> &towns);

#endif // HTASK3_H

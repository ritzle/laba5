#include "hTask3.h"

using namespace std;

void creatTrain(vector<trainInfo> &trains, vector<townInfo> &towns)
{
    cout << "Enter name train: ";
    string nameTrain;
    cin >> nameTrain;

    // Найдем или создадим структуру для train
    trainInfo *pTrain = nullptr;
    for (auto &train : trains)
    {
        if (train.name == nameTrain)
        {
            pTrain = &train;
            break;
        }
    }
    if (pTrain == nullptr)
    {
        trains.emplace_back(trainInfo{nameTrain, {}});
        pTrain = &trains.back();
    }

    // Очистка буфера ввода
    std::cin.clear();                                                   // очистка флагов ошибок
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера до конца строки

    cout << "Enter all stops in a row: ";
    string allTown;
    getline(cin, allTown);

    istringstream iss(allTown); // позволяет работать с строкой как с потоком ввода

    if (!iss) // проверка ограничений
    {
        cout << "Error";
        return;
    }

    string town; // слово из строки allTown

    size_t numStations = 0;
    while (iss >> town)
    {
        pTrain->stationTown.push_back(town);
        creatTown(nameTrain, town, towns);
        numStations++;
    }

    // Проверяем, что количество станций больше 1
    if (numStations <= 1 && pTrain->stationTown.empty())
    {
        // Удаляем поезд из вектора trains
        auto trainIt = find_if(trains.begin(), trains.end(), [&](const trainInfo &train)
                               { return train.name == nameTrain; });
        if (trainIt != trains.end())
            trains.erase(trainIt);
    }

    return;
}

void creatTown(string nameTrain, string nameTown, vector<townInfo> &towns)
{

    townInfo *pTown = nullptr;
    for (auto &itTown : towns)
    {
        if (itTown.name == nameTown)
        {
            pTown = &itTown;
            break;
        }
    }
    if (pTown == nullptr)
    {
        towns.emplace_back(townInfo{nameTown, {}});
        pTown = &towns.back();
    }

    pTown->passingTrain.push_back(nameTrain);
}

void trainsForTown(std::string town, vector<townInfo> &towns)
{
    townInfo *pTown = nullptr;
    for (auto &itTown : towns)
    {
        if (itTown.name == town)
        {
            pTown = &itTown;
            break;
        }
    }
    if (pTown == nullptr)
    {
        cout << "there is no such city" << endl;
        return;
    }

    cout << "town: " << town << " - train: ";
    for (auto i : pTown->passingTrain)
    {
        cout << i << " ";
    }

    cout << endl;
}

void trainsForTownDop(std::string town, std::string train, vector<townInfo> &towns)
{
    townInfo *pTown = nullptr;
    for (auto &itTown : towns)
    {
        if (itTown.name == town)
        {
            pTown = &itTown;
            break;
        }
    }
    if (pTown == nullptr)
    {
        cout << "there is no such city" << endl;
        return;
    }

    for (auto i : pTown->passingTrain)
    {
        if (i != train)
        {
            cout << i << " ";
        }
    }
}

void townsForTrain(std::string nameTrain, vector<trainInfo> &train, vector<townInfo> &towns)
{

    trainInfo *pTrain = nullptr;
    for (auto &itTrain : train)
    {
        if (itTrain.name == nameTrain)
        {
            pTrain = &itTrain;
            break;
        }
    }
    if (pTrain == nullptr)
    {
        cout << "Error";
        return;
    }

    cout << "train: " << pTrain->name << "  town: ";
    for (auto i : pTrain->stationTown)
    {
        cout << i << "(";
        trainsForTownDop(i, nameTrain, towns);
        cout << ")" << " - ";
    }

    cout << endl;

    return;
}

void coutTrains(vector<trainInfo> &trains)
{
    for (auto train : trains)
    {
        cout << "Train: " << train.name << " - " << train.stationTown << endl;
    }
}
#include "hTask3.h"
#include <set>
#include <unordered_set>

using namespace std;

void creatTrain(deque<trainInfo> &trains, deque<townInfo> &towns)
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
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter all stops in a row: ";
    string allTown;
    getline(cin, allTown);

    istringstream iss(allTown);

    if (!iss)
    {
        cout << "Error";
        return;
    }

    string town;
    set<string> onlyTown;
    deque<string> stationTown;

    while (iss >> town)
    {
        onlyTown.insert(town); // Добавляем город в множество для удаления дубликатов
    }

    // Заполняем список станций без повторяющихся городов
    stationTown.assign(onlyTown.begin(), onlyTown.end());

    if (stationTown.size() > 1)
    {
        pTrain->stationTown = std::move(stationTown);
        for (const auto &i : onlyTown)
        {
            creatTown(nameTrain, i, towns);
        }
    }
    else
    {
        cout << "Error: there must be more than 1 stations" << endl;
    }

    return;
}

void creatTown(string nameTrain, string nameTown, deque<townInfo> &towns)
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

void trainsForTown(std::string town, deque<townInfo> &towns)
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

void trainsForTownDop(std::string town, std::string train, deque<townInfo> &towns)
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

void townsForTrain(std::string nameTrain, deque<trainInfo> &train, deque<townInfo> &towns)
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
        cout << "there is no such train" << endl;
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

void coutTrains(const std::deque<trainInfo> &trains)
{
    for (const auto &train : trains)
    {
        std::cout << "Train: " << train.name << " - ";
        bool first = true;
        for (const auto &station : train.stationTown)
        {
            if (!first)
            {
                std::cout << " - ";
            }
            std::cout << station;
            first = false;
        }
        std::cout << std::endl;
    }
}
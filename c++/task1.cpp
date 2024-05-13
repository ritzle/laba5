
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>

using namespace std;

bool addProduct(string nameProduct, int countProduct, string cellAddress, map<char, vector<vector<vector<map<string, int>>>>> &stock);
int quantityShelfOccupancy(map<char, vector<vector<vector<map<string, int>>>>> &stock, char storageArea, int numberRack, int numberVerticalSection, int shelfNumber);

bool removeProduct(string nameProduct, int countProduct, string cellAddress, map<char, vector<vector<vector<map<string, int>>>>> &stock);
void REM(map<char, vector<vector<vector<map<string, int>>>>> &stock);

void INFO(const map<char, vector<vector<vector<map<string, int>>>>> &stock);
void ADD(map<char, vector<vector<vector<map<string, int>>>>> &stock);

/*
2-зоны хранения - ключ к 1 map
4-стелажа - первый vector
18-вертикальных секций - второй вектор
5-количество полок - 3 вектор
7200 - единиц вместимости
*/
#define MAX_CELL_SIZE 10
#define TOTAL_NUMBER_RACK 4
#define TOTAL_NUMBER_VERTICAL_SELECTION 18
#define TOTAL_SHELF_NUMBER 5
#define TOTAL_PRODUCT_STOCK 7200

int main()
{
    map<char, vector<vector<vector<map<string, int>>>>> stock;

    char action;

    cout << "A = ADD R = REMOVE I = INFO Q = exit" << endl;

    while (true)
    {
        cout << endl;
        cout << "Enter action: ";
        cin >> action;
        switch (action)
        {
        case 'A':
            ADD(stock);
            break;
        case 'R':
            REM(stock);
            break;
        case 'I':
            INFO(stock);
            cout << endl;
            break;
        case 'Q':
            return 0;
        default:
            cout << "unknown team\n";
        }
    }
}

bool addProduct(string nameProduct, int countProduct, string cellAddress, map<char, vector<vector<vector<map<string, int>>>>> &stock)
{
    if (countProduct > 10)
    {
        cout << "cell can only store 10 units\n";
        return false;
    }

    char storageArea = cellAddress[0];
    int numberRack = stoi(cellAddress.substr(1, 2)) - 1;
    int numberVerticalSection = stoi(cellAddress.substr(3, 2)) - 1;
    int shelfNumber = stoi(cellAddress.substr(5, 6)) - 1;

    // ограничение склада
    if (storageArea != 'A' && storageArea != 'B' || numberRack < 0 || numberRack >= TOTAL_NUMBER_RACK || numberVerticalSection < 0 || numberVerticalSection >= TOTAL_NUMBER_VERTICAL_SELECTION || shelfNumber < 0 || shelfNumber >= TOTAL_SHELF_NUMBER)
    {
        cout << "Invalid cell address" << endl;
        return false;
    }

    if (stock.count(storageArea) == 0)
    {
        stock[storageArea] = vector<vector<vector<map<string, int>>>>(TOTAL_NUMBER_RACK, vector<vector<map<string, int>>>(TOTAL_NUMBER_VERTICAL_SELECTION, vector<map<string, int>>(TOTAL_SHELF_NUMBER)));
    }

    // смотрим сколько едениц продуктов на полке
    int numberProductUnitsShelf = quantityShelfOccupancy(stock, storageArea, numberRack, numberVerticalSection, shelfNumber);

    if ((numberProductUnitsShelf + countProduct) <= MAX_CELL_SIZE)
    {
        auto &innerMap = stock[storageArea][numberRack][numberVerticalSection][shelfNumber];
        innerMap[nameProduct] += countProduct;
        return true;
    }
    else
    {
        cout << "now on the shelf " << numberProductUnitsShelf << endl;
        cout << "total shelf can store " << MAX_CELL_SIZE << " units of product" << endl;
        return false;
    }
}

void INFO(const map<char, vector<vector<vector<map<string, int>>>>> &stock)
{
    if (stock.empty())
    {
        cout << "Stock empty" << endl;
        return;
    }

    float counterProduct = 0;
    float counterProductSectorA = 0;
    float counterProductSectorB = 0;

    for (auto &map1 : stock)
    {
        for (size_t vector1 = 0; vector1 < map1.second.size(); vector1++)
        {
            for (size_t vector2 = 0; vector2 < map1.second[vector1].size(); vector2++)
            {
                for (size_t vector3 = 0; vector3 < map1.second[vector1][vector2].size(); vector3++)
                {
                    for (auto &map2 : map1.second[vector1][vector2][vector3])
                    {
                        counterProduct += map2.second;
                        if (map1.first == 'A')
                        {
                            counterProductSectorA += map2.second;
                        }
                        else if (map1.first == 'B')
                        {
                            counterProductSectorB += map2.second;
                        }

                        if (map2.second != 0)
                        {
                            cout << map1.first << "-" << vector1 + 1 << "-" << vector2 + 1 << "-" << vector3 + 1 << "-" << map2.first << " = " << map2.second << endl;
                        }
                    }
                }
            }
        }
        if (map1.first == 'A')
        {
            cout << (counterProductSectorA * 100) / (TOTAL_PRODUCT_STOCK / 2) << "% - sector A" << endl;
        }
        else if (map1.first == 'B')
        {
            cout << (counterProductSectorB * 100) / (TOTAL_PRODUCT_STOCK / 2) << "% - sector B" << endl;
        }
        cout << endl;
    }
    cout << endl;
    cout << (counterProduct * 100) / TOTAL_PRODUCT_STOCK << "% - fullness";
}

void ADD(map<char, vector<vector<vector<map<string, int>>>>> &stock)
{
    string nameProduct;
    int countProduct;
    string cellAddress;

    cout << "nameProduct: ";
    cout << "countProduct: ";
    cout << "cellAddress: ";
    cin >> nameProduct >> countProduct >> cellAddress;
    if (cellAddress.size() != 7)
    {
        cout << "error";
        return;
    }

    if (addProduct(nameProduct, countProduct, cellAddress, stock))
    {
        cout << "product added\n";
    }
    else
    {
        cout << "product not added\n";
    }
}

int quantityShelfOccupancy(map<char, vector<vector<vector<map<string, int>>>>> &stock, char storageArea, int numberRack, int numberVerticalSection, int shelfNumber)
{
    int numberProductUnitsShelf = 0;

    if (stock.count(storageArea) > 0 && numberRack >= 0 && numberRack < TOTAL_NUMBER_RACK && numberVerticalSection >= 0 && numberVerticalSection < TOTAL_NUMBER_VERTICAL_SELECTION && shelfNumber >= 0 && shelfNumber < TOTAL_SHELF_NUMBER)
    {
        auto &innerMap = stock[storageArea][numberRack][numberVerticalSection][shelfNumber];

        for (auto &product : innerMap)
        {
            numberProductUnitsShelf += product.second;
        }
    }

    return numberProductUnitsShelf;
}

bool removeProduct(string nameProduct, int countProduct, string cellAddress, map<char, vector<vector<vector<map<string, int>>>>> &stock)
{
    if (countProduct > 10)
    {
        cout << "No more than 10 can be deleted at a time\n";
        return false;
    }

    char storageArea = cellAddress[0];
    int numberRack = stoi(cellAddress.substr(1, 2)) - 1;
    int numberVerticalSection = stoi(cellAddress.substr(3, 2)) - 1;
    int shelfNumber = stoi(cellAddress.substr(5, 6)) - 1;

    // ограничение склада
    if (storageArea != 'A' && storageArea != 'B' || numberRack < 0 || numberRack >= TOTAL_NUMBER_RACK || numberVerticalSection < 0 || numberVerticalSection >= TOTAL_NUMBER_VERTICAL_SELECTION || shelfNumber < 0 || shelfNumber >= TOTAL_SHELF_NUMBER)
    {
        cout << "Invalid cell address" << endl;
        return false;
    }

    if (stock.empty())
    {
        cout << "Stock empty";
        return 0;
    }

    auto &innerMap = stock[storageArea][numberRack][numberVerticalSection][shelfNumber];

    if (innerMap.find(nameProduct) != innerMap.end())
    {
        if ((innerMap[nameProduct] - countProduct) < 0)
        {
            cout << nameProduct << " is less of this product than you want to remove" << endl;
            return 0;
        }
        else
        {
            innerMap[nameProduct] -= countProduct;

            if (innerMap[nameProduct] == 0)
            {
                innerMap.erase(nameProduct);
            }

            return 1;
        }
    }
    else
    {
        cout << "product not finded" << endl;
        return 0;
    }
}

void REM(map<char, vector<vector<vector<map<string, int>>>>> &stock)
{
    string nameProduct;
    int countProduct;
    string cellAddress;

    cout << "nameProduct: ";
    cout << "countProduct: ";
    cout << "cellAddress: ";
    cin >> nameProduct >> countProduct >> cellAddress;

    if (removeProduct(nameProduct, countProduct, cellAddress, stock))
    {
        cout << "product remove\n";
    }
    else
    {
        cout << "product not remove\n";
    }
}
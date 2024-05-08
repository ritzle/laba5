#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

// TODO: добавить тесты

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const set<T> &nums) // возвращаем ссылку на поток что бы cout мог ухватиться и вывести что-то следом
{
    for (auto i : nums)
    {
        os << i << " ";
    }
    return os;
}

struct infoPeople
{
    string name;
    set<string> allFriend;
};

void friends(string nameOne, string nameTwo, vector<infoPeople> &people);
void printFriend(vector<infoPeople> &people);
int countFriends(string name, vector<infoPeople> &people);
bool questionFriends(const string &nameOne, const string &nameTwo, const vector<infoPeople> &people);

int main()
{
    vector<infoPeople> people;

    friends("Peter", "Goward", people);
    cout << countFriends("Sally", people) << endl;
    friends("Goward", "Sally", people);
    cout << countFriends("Goward", people) << endl;
    cout << countFriends("Peter", people) << endl;
    cout << (questionFriends("Goward", "Peter", people) ? "YES" : "NO") << endl;
    cout << (questionFriends("Peter", "Sally", people) ? "YES" : "NO") << endl;
    cout << (questionFriends("Jenny", "jastin", people) ? "YES" : "NO") << endl;
    // printFriend(people);
}

void friends(string nameOne, string nameTwo, vector<infoPeople> &people)
{
    // Найдем или создадим структуру для nameOne
    infoPeople *personOne = nullptr;
    for (auto &person : people)
    {
        if (person.name == nameOne)
        {
            personOne = &person;
            break;
        }
    }
    if (personOne == nullptr)
    {
        people.emplace_back(infoPeople{nameOne, {}});
        personOne = &people.back();
    }
    personOne->allFriend.emplace(nameTwo);

    // Найдем или создадим структуру для nameTwo
    infoPeople *personTwo = nullptr;
    for (auto &person : people)
    {
        if (person.name == nameTwo)
        {
            personTwo = &person;
            break;
        }
    }
    if (personTwo == nullptr)
    {
        people.emplace_back(infoPeople{nameTwo, {}});
        personTwo = &people.back();
    }
    personTwo->allFriend.emplace(nameOne);
}

void printFriend(vector<infoPeople> &people)
{
    for (auto &person : people)
    {
        cout << person.name << " - " << person.allFriend << endl;
    }
}

int countFriends(string name, vector<infoPeople> &people)
{

    infoPeople *pPerson = nullptr;

    for (auto &person : people)
    {
        if (name == person.name)
        {
            pPerson = &person;
        }
    }

    if (pPerson == nullptr)
    {
        return 0;
    }
    else
    {
        return pPerson->allFriend.size();
    }
}

bool questionFriends(const string &nameOne, const string &nameTwo, const vector<infoPeople> &people)
{
    // Поиск человека с именем nameOne
    // использование иттератора, передаем лямбда функцию
    auto itPersonOne = find_if(people.begin(), people.end(), [&](const infoPeople &person)
                               { return person.name == nameOne; });
    if (itPersonOne == people.end())
    {
        return false;
    }

    // Поиск человека с именем nameTwo
    auto itPersonTwo = find_if(people.begin(), people.end(), [&](const infoPeople &person)
                               { return person.name == nameTwo; });
    if (itPersonTwo == people.end())
    {
        return false;
    }

    // Проверка, являются ли они друзьями
    return (find(itPersonOne->allFriend.begin(), itPersonOne->allFriend.end(), nameTwo) != itPersonOne->allFriend.end() &&
            find(itPersonTwo->allFriend.begin(), itPersonTwo->allFriend.end(), nameOne) != itPersonTwo->allFriend.end());
}

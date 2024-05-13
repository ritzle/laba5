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

    char action;
    cout << endl;
    cout << "Enter action: ";
    cin >> action;
    switch (action)
    {

    case '0':

        cout << "enter n: ";

        int n;
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "Enter a request (FRIENDS, COUNT, QUESTION, or E to exit): ";
            string request;
            cin >> request;

            if (request == "E")
                break;

            if (request == "FRIENDS")
            {
                string name1, name2;
                cout << "Enter two names: ";
                cin >> name1 >> name2;
                friends(name1, name2, people);
            }
            else if (request == "COUNT")
            {
                string name;
                cout << "Enter a name: ";
                cin >> name;
                cout << "Number of friends for " << name << ": " << countFriends(name, people) << endl;
            }
            else if (request == "QUESTION")
            {
                string name1, name2;
                cout << "Enter two names: ";
                cin >> name1 >> name2;
                cout << (questionFriends(name1, name2, people) ? "YES" : "NO") << endl;
            }
            else
            {
                cout << "Invalid request. Please try again." << endl;
            }
        }
        break;

    case '1':
        friends("Peter", "Peter", people);
        cout << countFriends("Sally", people) << endl;
        friends("Goward", "Sally", people);
        cout << countFriends("Goward", people) << endl;
        cout << countFriends("Peter", people) << endl;
        cout << (questionFriends("Goward", "Peter", people) ? "YES" : "NO") << endl;
        cout << (questionFriends("Peter", "Sally", people) ? "YES" : "NO") << endl;
        cout << (questionFriends("Jenny", "jastin", people) ? "YES" : "NO") << endl;

        break;

    case '2':

        friends("Alice", "Bob", people);
        friends("Bob", "Charlie", people);
        cout << countFriends("Alice", people) << endl;
        cout << countFriends("Bob", people) << endl;
        cout << countFriends("Charlie", people) << endl;
        cout << (questionFriends("Alice", "Bob", people) ? "YES" : "NO") << endl;
        cout << (questionFriends("Bob", "Charlie", people) ? "YES" : "NO") << endl;
        cout << (questionFriends("Alice", "Charlie", people) ? "YES" : "NO") << endl;
        break;

    case '3':
        cout << countFriends("John", people) << endl;
        cout << countFriends("Jane", people) << endl;
        cout << (questionFriends("John", "Jane", people) ? "YES" : "NO") << endl;
        break;

    case '4':
        friends("Emily", "Olivia", people);
        cout << (questionFriends("Emily", "Olivia", people) ? "YES" : "NO") << endl;
        cout << (questionFriends("Emily", "David", people) ? "YES" : "NO") << endl;
        break;

    case '5':
        friends("Alice", "Bob", people);
        friends("Alice", "Charlie", people);
        friends("Alice", "David", people);
        friends("Alice", "Emily", people);
        friends("Bob", "Charlie", people);
        friends("David", "Emily", people);
        friends("Charlie", "Emily", people);

        cout << countFriends("Alice", people) << endl;   // Вывод: 4
        cout << countFriends("Bob", people) << endl;     // Вывод: 2
        cout << countFriends("Charlie", people) << endl; // Вывод: 3
        cout << countFriends("David", people) << endl;   // Вывод: 2
        cout << countFriends("Emily", people) << endl;   // Вывод: 3

        cout << (questionFriends("Alice", "Bob", people) ? "YES" : "NO") << endl;     // Вывод: YES
        cout << (questionFriends("Alice", "Charlie", people) ? "YES" : "NO") << endl; // Вывод: YES
        cout << (questionFriends("Alice", "David", people) ? "YES" : "NO") << endl;   // Вывод: YES
        cout << (questionFriends("Alice", "Emily", people) ? "YES" : "NO") << endl;   // Вывод: YES
        cout << (questionFriends("Bob", "Charlie", people) ? "YES" : "NO") << endl;   // Вывод: YES
        cout << (questionFriends("David", "Emily", people) ? "YES" : "NO") << endl;   // Вывод: YES
        cout << (questionFriends("Charlie", "Emily", people) ? "YES" : "NO") << endl;
        break;

    case 'E':
        return 0;
    default:
        cout << "unknown team\n";
    }
    // printFriend(people);
}

void friends(string nameOne, string nameTwo, vector<infoPeople> &people)
{

    if (nameOne == nameTwo)
    {
        return;
    }
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

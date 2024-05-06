#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

void Datainput(map<int, vector<pair<string, int>>> &queue);
int findingMinTime(map<int, vector<pair<string, int>>> &queue);
string ticketGeneration(map<int, vector<pair<string, int>>> &queue);
void printQueue(map<int, vector<pair<string, int>>> &queue);
int allTimeWindows(map<int, vector<pair<string, int>>> &queue, int windows);

int main()
{

    int numberWindows;
    cout << "enter number of windows: ";
    cin >> numberWindows;

    map<int, vector<pair<string, int>>> queue;

    for (int i = 0; i < numberWindows; i++)
    {
        queue[i] = vector<pair<string, int>>();
    }

    Datainput(queue);

    return 0;
}

void Datainput(map<int, vector<pair<string, int>>> &queue)
{

    while (true)
    {
        cout << ": ";
        string request;
        cin >> request;

        if (request == "ENQUEUE")
        {
            int time;
            cin >> time;

            string ticket = ticketGeneration(queue);

            int numWindows = findingMinTime(queue);
            queue[numWindows].push_back(make_pair(ticket, time));
            cout << ticket << endl;
        }
        else if (request == "DISTRIBUTE")
        {
            printQueue(queue);
            break;
        }
        else
        {
            cout << "Error. Re-enter\n";
        }
    }

    return;
}

int findingMinTime(map<int, vector<pair<string, int>>> &queue)
{
    int NumberWindows = 0;
    int minTime = 0;

    for (auto pair : queue[0])
    {
        minTime += pair.second;
    }

    for (auto windows : queue)
    {
        int time = 0;
        for (auto ticket : windows.second)
        {
            time += ticket.second;
        }

        if (time < minTime)
        {
            NumberWindows = windows.first;
        }
    }

    return NumberWindows;
}

string ticketGeneration(map<int, vector<pair<string, int>>> &queue)
{
    string ticket;
    bool uniqueTicket = false;

    while (!uniqueTicket)
    {
        // Генерируем случайное число для талона
        srand(time(0));
        int randTicket = rand() % 1000;
        ticket = "T" + to_string(randTicket);

        // Проверяем, есть ли такой талон в map
        uniqueTicket = true;
        for (auto map : queue)
        {
            for (auto pair : map.second)
            {
                if (pair.first == ticket)
                {
                    uniqueTicket = false;
                    break;
                }
            }
            if (!uniqueTicket)
            {
                break;
            }
        }
    }

    return ticket;
}

void printQueue(map<int, vector<pair<string, int>>> &queue)
{
    int win = 0;
    for (auto windows : queue)
    {
        int allTime = allTimeWindows(queue, win);
        win++;
        cout << "Windows " << windows.first + 1 << " " << allTime << " minutes "
             << ": "; //+1 для вывода с 1 кона
        for (auto ticket : windows.second)
        {
            cout << ticket.first << " ";
        }

        cout << endl;
    }
}

int allTimeWindows(map<int, vector<pair<string, int>>> &queue, int windows)
{
    int time = 0;

    for (auto ticket : queue[windows])
    {
        time += ticket.second;
    }

    return time;
}

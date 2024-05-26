#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

// Define the cities and their connections
map<string, map<string, int>> graph = {
    {"A", {{"B", 2}, {"C", 4}}},
    {"B", {{"A", 4}, {"D", 3}, {"E", 1}}},
    {"C", {{"A", 2}, {"F", 5}}},
    {"D", {{"B", 3}, {"G", 7}}},
    {"E", {{"B", 1}, {"G", 2}}},
    {"F", {{"C", 4}, {"G", 1}}},
    {"G", {{"D", 7}, {"E", 1}, {"F", 1}}}};

// Heuristic function (straight-line distance to Bucharest)
map<string, int> heuristic = {
    {"A", 6}, {"B", 4}, {"C", 3}, {"D", 4}, {"E", 2}, {"F", 1}, {"G", 0}};

// A* Search function
vector<string> aStarSearch(const string &start, const string &goal)
{
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> frontier;
    map<string, string> cameFrom; // to keep track of the parent node for each node encountered during the search
    map<string, int> costSoFar;

    frontier.push({heuristic[start], start});
    cameFrom[start] = "";
    costSoFar[start] = 0;

    while (!frontier.empty())
    {
        string current = frontier.top().second;
        frontier.pop();

        if (current == goal)
        {
            vector<string> path;
            while (current != "")
            {
                path.push_back(current);
                current = cameFrom[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto &neighbor : graph[current])
        {
            string next = neighbor.first;
            int newCost = costSoFar[current] + neighbor.second; // total cost of reaching the neighboring node as per graph

            if (costSoFar.find(next) == costSoFar.end())
            { // if next has not been visited or if the new cost to reach next is lower than the previously recorded cost
                costSoFar[next] = newCost;
                cameFrom[next] = current;
                int priority = newCost + heuristic[next];
                frontier.push({priority, next});
            }
        }
    }

    return {}; // No path found
}

int main()
{
    string start = "A";
    string goal = "G";

    vector<string> path = aStarSearch(start, goal);

    if (!path.empty())
    {
        cout << "Shortest path from " << start << " to " << goal << ":\n";
        for (const string &city : path)
        {
            cout << city;
            if (city != goal)
            {
                cout << " -> ";
            }
        }
        cout << "\nGoal reached.\n";
    }
    else
    {
        cout << "No path found from " << start << " to " << goal << ".\n";
    }

    return 0;
}

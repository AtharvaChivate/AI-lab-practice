#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Node
{
public:
    int missionaries;
    int cannibals;
    int boat;
    Node *parent;

    Node(int missionaries, int cannibals, int boat, Node *parent) : missionaries(missionaries), cannibals(cannibals), boat(boat), parent(parent) {}

    bool isValid()
    {
        if (missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals > 3)
        {
            return false;
        }

        if ((missionaries < cannibals && missionaries > 0) || (missionaries > cannibals && missionaries < 3))
        {
            return false;
        }

        return true;
    }

    bool isGoal()
    {
        return missionaries == 0 && cannibals == 0 && boat == 0;
    }

    vector<Node *> getNextStates()
    {
        vector<Node *> nextStates;

        int newBoat = 1 - boat;

        for (int m = 0; m <= 2; m++)
        {
            for (int c = 0; c <= 2; c++)
            {
                if (m + c >= 1 && m + c <= 2)
                {
                    int newMissionaries = missionaries - m * boat + m * newBoat;
                    int newCannibals = cannibals - c * boat + c * newBoat;

                    Node *nextState = new Node(newMissionaries, newCannibals, newBoat, this);

                    if (nextState->isValid())
                    {
                        nextStates.push_back(nextState);
                    }
                }
            }
        }

        return nextStates;
    }
};

void printSolution(Node *goalNode);

void bfs()
{
    queue<Node *> q;
    unordered_set<Node *> visited;

    Node *initialState = new Node(3, 3, 1, nullptr);
    q.push(initialState);
    visited.insert(initialState);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        if (current->isGoal())
        {
            printSolution(current);
            return;
        }

        vector<Node *> nextStates = current->getNextStates();

        for (Node *nextState : nextStates)
        {
            if (visited.find(nextState) == visited.end())
            {
                q.push(nextState);
                visited.insert(nextState);
            }
        }
    }

    cout << "No solution found." << endl;
}

void printSolution(Node *goalNode)
{
    vector<Node *> path;

    while (goalNode != nullptr)
    {
        path.push_back(goalNode);
        goalNode = goalNode->parent;
    }

    reverse(path.begin(), path.end());

    for (Node *node : path)
    {
        cout << "(" << node->missionaries << ", " << node->cannibals << ", " << node->boat << ")" << endl;
    }

    cout << "Goal State Reached!" << endl;
}

int main()
{
    bfs();
    return 0;
}

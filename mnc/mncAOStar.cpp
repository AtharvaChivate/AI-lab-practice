#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional> // Needed for std::function
#include <algorithm>

using namespace std;

class Node
{
public:
    int missionaries;
    int cannibals;
    int boat; // 1 for the original side, 0 for the other side
    Node *parent;
    int cost;      // Cost from start to current state
    int heuristic; // Heuristic value

    Node(int missionaries, int cannibals, int boat, Node *parent) : missionaries(missionaries), cannibals(cannibals), boat(boat), parent(parent)
    {
        this->cost = (parent != nullptr) ? parent->cost + 1 : 0; // Increment cost from parent
        this->heuristic = estimateHeuristic();
    }

    // Check if the current state is a valid state
    bool isValid()
    {
        if (missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals > 3)
        {
            return false;
        }
        return (missionaries >= cannibals || missionaries == 0) &&
               (missionaries <= cannibals || missionaries == 3);
    }

    // Check if the current state is the goal state
    bool isGoal()
    {
        return missionaries == 0 && cannibals == 0 && boat == 0;
    }

    // Get possible next states from the current state
    vector<Node *> getNextStates()
    {
        vector<Node *> nextStates;

        int newBoat = 1 - boat; // Flip the boat side

        // Generate possible combinations of missionaries and cannibals to move
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
                    else
                    {
                        delete nextState; // Clean up invalid states
                    }
                }
            }
        }

        return nextStates;
    }

    // Heuristic function for estimating the cost to the goal
    int estimateHeuristic()
    {
        // Simple heuristic: Number of missionaries and cannibals on the starting side
        return missionaries + cannibals;
    }

    // Override equality operator to use in unordered_set
    bool operator==(const Node &other) const
    {
        return missionaries == other.missionaries &&
               cannibals == other.cannibals &&
               boat == other.boat;
    }

    // Hash function for unordered_set
    struct Hash
    {
        size_t operator()(const Node *node) const
        {
            return hash<int>()(node->missionaries) ^
                   hash<int>()(node->cannibals) ^
                   hash<int>()(node->boat);
        }
    };
};

void printSolution(Node *goalNode)
{
    vector<Node *> path;
    unordered_set<Node *, Node::Hash> visitedStates; // Keep track of visited states

    // Build the path from the initial state to the goal state
    while (goalNode != nullptr)
    {
        path.push_back(goalNode);
        goalNode = goalNode->parent;
    }

    // Print the states in the correct order, skipping duplicates
    for (int i = path.size() - 1; i >= 0; i--)
    {
        Node *node = path[i];

        // Check if the state has already been visited
        if (visitedStates.find(node) == visitedStates.end())
        {
            cout << "(" << node->missionaries << ", " << node->cannibals << ", " << node->boat << ")" << endl;
            visitedStates.insert(node); // Mark the state as visited
        }
    }
}

// Method to update the heuristic dynamically
void updateHeuristic(Node *node)
{
    // Here, you can implement a policy to update the heuristic dynamically.
    // For simplicity, let's say we decrease the heuristic by a fixed amount.
    node->heuristic -= 1;
}

void aoStar()
{
    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> priorityQueue(
        [](Node *a, Node *b)
        {
            return (a->cost + a->heuristic) > (b->cost + b->heuristic);
        });
    unordered_set<Node *, Node::Hash> visitedStates;

    Node *initialState = new Node(3, 3, 1, nullptr);
    priorityQueue.push(initialState);

    while (!priorityQueue.empty())
    {
        Node *current = priorityQueue.top();
        priorityQueue.pop();

        // Print the current state when it is chosen for expansion
        // cout << "(" << current->missionaries << ", " << current->cannibals << ", " << current->boat << ")" << endl;

        if (current->isGoal())
        {
            cout << "Goal state reached!" << endl;
            printSolution(current);
            return;
        }

        visitedStates.insert(current);

        vector<Node *> nextStates = current->getNextStates();
        for (Node *nextState : nextStates)
        {
            if (visitedStates.find(nextState) == visitedStates.end())
            {
                priorityQueue.push(nextState);
            }
            else
            {
                delete nextState; // Clean up visited states
            }
        }

        // Update the heuristic dynamically
        updateHeuristic(current);
    }

    cout << "No solution found." << endl;
}

int main()
{
    aoStar();
    return 0;
}

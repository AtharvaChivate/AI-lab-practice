#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional> // for std::function
#include <algorithm> // for std::max

using namespace std;

class Node {
public:
    int missionaries;
    int cannibals;
    int boat;
    Node* parent;
    int heuristic; // Heuristic value

    Node(int missionaries, int cannibals, int boat, Node* parent) : missionaries(missionaries), cannibals(cannibals), boat(boat), parent(parent) {
        heuristic = estimateHeuristic();
    }

    bool isValid() {
        if (missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals > 3) {
            return false;
        }
        return (missionaries >= cannibals || missionaries == 0) && (missionaries <= cannibals || missionaries == 3);
    }

    bool isGoal() {
        return missionaries == 0 && cannibals == 0 && boat == 0;
    }

    vector<Node*> getNextStates() {
        vector<Node*> nextStates;

        int newBoat = 1 - boat;

        for (int m = 0; m <= 2; m++) {
            for (int c = 0; c <= 2; c++) {
                if (m + c >= 1 && m + c <= 2) {
                    int newMissionaries = missionaries - m * boat + m * newBoat;
                    int newCannibals = cannibals - c * boat + c * newBoat;

                    Node* nextState = new Node(newMissionaries, newCannibals, newBoat, this);

                    if (nextState->isValid()) {
                        nextStates.push_back(nextState);
                    }
                }
            }
        }

        return nextStates;
    }

    bool operator==(const Node& other) const {
        return missionaries == other.missionaries && cannibals == other.cannibals && boat == other.boat;
    }

private:
    int estimateHeuristic() {
        // Simple heuristic: Number of missionaries and cannibals on the starting side
        return missionaries + cannibals;
    }
};

// Custom comparator for priority queue based on heuristic value
class NodeComparator {
public:
    bool operator()(const Node* a, const Node* b) const {
        return a->heuristic > b->heuristic; // Min-heap based on heuristic
    }
};

void printSolution(Node* goalNode);

void bestFirstSearch() {
    priority_queue<Node*, vector<Node*>, NodeComparator> priorityQueue;
    unordered_set<Node*> visitedStates;

    Node* initialState = new Node(3, 3, 1, nullptr);
    priorityQueue.push(initialState);

    while (!priorityQueue.empty()) {
        Node* current = priorityQueue.top();
        priorityQueue.pop();

        if (current->isGoal()) {
            cout << "Goal state reached!" << endl;
            printSolution(current);
            return;
        }

        visitedStates.insert(current);

        vector<Node*> nextStates = current->getNextStates();
        for (Node* nextState : nextStates) {
            if (visitedStates.find(nextState) == visitedStates.end()) {
                priorityQueue.push(nextState);
            }
        }
    }

    cout << "No solution found." << endl;
}

void printSolution(Node* goalNode) {
    vector<Node*> path;
    unordered_set<Node*> visitedStates; // Keep track of visited states

    // Build the path from the initial state to the goal state
    while (goalNode != nullptr) {
        path.push_back(goalNode);
        goalNode = goalNode->parent;
    }

    // Print the states in the correct order, skipping duplicates
    for (int i = path.size() - 1; i >= 0; i--) {
        Node* node = path[i];

        // Check if the state has already been visited
        if (visitedStates.find(node) == visitedStates.end()) {
            cout << "(" << node->missionaries << ", " << node->cannibals << ", " << node->boat << ")" << endl;
            visitedStates.insert(node); // Mark the state as visited
        }
    }
}

int main() {
    bestFirstSearch();
    return 0;
}

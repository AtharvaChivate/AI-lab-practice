#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

class Node {
public:
    int missionaries;
    int cannibals;
    int boat;
    Node* parent;

    Node(int missionaries, int cannibals, int boat, Node* parent) : missionaries(missionaries), cannibals(cannibals), boat(boat), parent(parent) {}

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
};

namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            size_t hashVal = 0;
            hashVal ^= hash<int>()(node.missionaries) + 0x9e3779b9 + (hashVal << 6) + (hashVal >> 2);
            hashVal ^= hash<int>()(node.cannibals) + 0x9e3779b9 + (hashVal << 6) + (hashVal >> 2);
            hashVal ^= hash<int>()(node.boat) + 0x9e3779b9 + (hashVal << 6) + (hashVal >> 2);
            return hashVal;
        }
    };
}

void printSolution(Node* goalNode);

void dfs() {
    stack<Node*> stack;
    unordered_set<Node> visitedStates;

    Node* initialState = new Node(3, 3, 1, nullptr);
    stack.push(initialState);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        if (current->isGoal()) {
            cout << "Goal state reached!" << endl;
            printSolution(current);
            return;
        }

        visitedStates.insert(*current);

        vector<Node*> nextStates = current->getNextStates();
        for (Node* nextState : nextStates) {
            if (visitedStates.find(*nextState) == visitedStates.end()) {
                stack.push(nextState);
            }
        }
    }

    cout << "No solution found." << endl;
}

void printSolution(Node* goalNode) {
    vector<Node*> path;

    while (goalNode != nullptr) {
        path.push_back(goalNode);
        goalNode = goalNode->parent;
    }

    for (int i = path.size() - 1; i >= 0; i--) {
        Node* node = path[i];
        cout << "(" << node->missionaries << ", " << node->cannibals << ", " << node->boat << ")" << endl;
    }
}

int main() {
    dfs();
    return 0;
}

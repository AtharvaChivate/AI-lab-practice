#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <cmath>
using namespace std;

// Forward declaration of heuristic function
int heuristic(vector<vector<int>>& board, vector<vector<int>>& goal);

// State struct definition
struct State {
    vector<vector<int>> board;
    int zr;
    int zc;
    State* parent;
    string action;
    int hn;

    State(vector<vector<int>>& board, int zr, int zc, State* parent, string action, int hn)
        : board(board), zr(zr), zc(zc), parent(parent), action(action), hn(hn) {}

    void display() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Comparator for priority queue
struct CompareState {
    bool operator()(State* s1, State* s2) {
        return s1->hn > s2->hn;
    }
};

// Function to calculate heuristic
int heuristic(vector<vector<int>>& board, vector<vector<int>>& goal) {
    int heuristic = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0) {
                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < 3; col++) {
                        if (goal[row][col] == board[i][j]) {
                            heuristic += abs(row - i) + abs(col - j);
                        }
                    }
                }
            }
        }
    }
    return heuristic;
}

// Function to get neighboring states
vector<State*> getNeighbours(State* state, vector<vector<int>>& goal) {
    vector<vector<int>> position = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    vector<State*> neighbouring;
    
    for (auto& pos : position) {
        int newzeror = state->zr + pos[0];
        int newzeroc = state->zc + pos[1];
        
        if (newzeror >= 0 && newzeror < 3 && newzeroc >= 0 && newzeroc < 3) {
            vector<vector<int>> newboard = state->board;
            swap(newboard[state->zr][state->zc], newboard[newzeror][newzeroc]);
            State* newstate = new State(newboard, newzeror, newzeroc, state, "Moved", heuristic(newboard, goal));
            neighbouring.push_back(newstate);
        }
    }
    
    return neighbouring;
}

// Function to print the path from initial state to goal state
void printPath(State* goalState, unordered_map<State*, State*>& path) {
    stack<State*> p1;
    State* itr = goalState;
    while (path[itr] != nullptr) {
        p1.push(itr);
        itr = path[itr];
    }
    p1.push(itr);
    while (!p1.empty()) {
        itr = p1.top();
        p1.pop();
        itr->display();
        cout << itr->action << " with heuristic -> " << itr->hn << endl;
    }
}

// Main function
int main() {
    vector<vector<int>> initial(3, vector<int>(3, 0));
    vector<vector<int>> goal(3, vector<int>(3, 0));
    int zr = 0, zc = 0;
    
    cout << "Enter the present board: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> initial[i][j];
            if (initial[i][j] == 0) {
                zr = i;
                zc = j;
            }
        }
    }

    cout << "Enter the goal board: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> goal[i][j];
        }
    }

    State* initialState = new State(initial, zr, zc, nullptr, "Root Node", heuristic(initial, goal));
    priority_queue<State*, vector<State*>, CompareState> pq;
    unordered_map<State*, State*> path;
    pq.push(initialState);

    bool foundGoal = false;
    State* goalState = nullptr;

    while (!pq.empty()) {
        State* currentState = pq.top();
        pq.pop();
        
        if (currentState->board == goal) {
            cout << "Goal reached" << endl;
            foundGoal = true;
            goalState = currentState;
            break;
        }
        
        vector<State*> neighbours = getNeighbours(currentState, goal);
        for (State* neighbour : neighbours) {
            if (currentState->parent != nullptr && currentState->parent->board == neighbour->board) {
                continue;
            }
            pq.push(neighbour);
            path[neighbour] = currentState;
        }
    }

    if (foundGoal) {
        printPath(goalState, path);
    } else {
        cout << "Goal state could not be found!" << endl;
    }

    return 0;
}


// input:
// 1 2 3
// 4 0 5
// 6 7 8

// output:
// 1 2 3
// 4 5 6
// 7 8 0
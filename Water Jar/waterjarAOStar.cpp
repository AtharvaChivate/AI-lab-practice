#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
using namespace std;

class AOStarState
{
public:
    int jug1;
    int jug2;
    int g; // Cost to reach this state from the initial state
    int h; // Heuristic value

    AOStarState(int jug1, int jug2, int g, int h) : jug1(jug1), jug2(jug2), g(g), h(h) {}

    bool operator==(const AOStarState &other) const
    {
        return jug1 == other.jug1 && jug2 == other.jug2;
    }
};

struct AOStarStateHash
{
    size_t operator()(const AOStarState &state) const
    {
        return hash<int>()(state.jug1) ^ hash<int>()(state.jug2);
    }
};

class CompareAOStarState
{
public:
    bool operator()(const AOStarState &s1, const AOStarState &s2)
    {
        return s1.g + s1.h > s2.g + s2.h;
    }
};

void solveWaterJug(int jug1Capacity, int jug2Capacity, int targetAmount)
{
    priority_queue<AOStarState, vector<AOStarState>, CompareAOStarState> queue;
    unordered_set<AOStarState, AOStarStateHash> visited;

    AOStarState initialState(0, 0, 0, abs(0 - targetAmount) + abs(0 - targetAmount));
    queue.push(initialState);

    while (!queue.empty())
    {
        AOStarState currentState = queue.top();
        queue.pop();
        cout << "Visited State: " << currentState.jug1 << " " << currentState.jug2 << endl;

        if (currentState.jug1 == targetAmount || currentState.jug2 == targetAmount)
        {
            cout << "Solution found: " << currentState.jug1 << " " << currentState.jug2 << endl;
            return;
        }

        visited.insert(currentState);

        // Generate successor states
        vector<AOStarState> successors;
        int pour1To2 = min(currentState.jug1, jug2Capacity - currentState.jug2);
        int pour2To1 = min(currentState.jug2, jug1Capacity - currentState.jug1);

        successors.push_back(AOStarState(jug1Capacity, currentState.jug2, currentState.g + 1, abs(jug1Capacity - targetAmount) + abs(currentState.jug2 - targetAmount)));
        successors.push_back(AOStarState(currentState.jug1, jug2Capacity, currentState.g + 1, abs(currentState.jug1 - targetAmount) + abs(jug2Capacity - targetAmount)));
        successors.push_back(AOStarState(currentState.jug1 - pour1To2, currentState.jug2 + pour1To2, currentState.g + 1, abs(currentState.jug1 - pour1To2 - targetAmount) + abs(currentState.jug2 + pour1To2 - targetAmount)));
        successors.push_back(AOStarState(currentState.jug1 + pour2To1, currentState.jug2 - pour2To1, currentState.g + 1, abs(currentState.jug1 + pour2To1 - targetAmount) + abs(currentState.jug2 - pour2To1 - targetAmount)));
        successors.push_back(AOStarState(0, currentState.jug2, currentState.g + 1, abs(0 - targetAmount) + abs(currentState.jug2 - targetAmount)));
        successors.push_back(AOStarState(currentState.jug1, 0, currentState.g + 1, abs(currentState.jug1 - targetAmount) + abs(0 - targetAmount)));

        for (const auto &successor : successors)
        {
            if (visited.find(successor) == visited.end())
            {
                queue.push(successor);
            }
        }
    }

    cout << "No solution found." << endl;
}

int main()
{
    int jug1Capacity = 4;
    int jug2Capacity = 3;
    int targetAmount = 2;

    solveWaterJug(jug1Capacity, jug2Capacity, targetAmount);

    return 0;
}

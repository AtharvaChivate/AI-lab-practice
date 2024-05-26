#include <iostream>
#include <queue>
#include <unordered_set>
#include <functional>
#include <cmath>

using namespace std;

struct State
{
    int a;
    int b;

    State(int a, int b) : a(a), b(b) {}

    bool operator==(const State &other) const
    {
        return a == other.a && b == other.b;
    }
};

struct StateHash
{
    size_t operator()(const State &state) const
    {
        return hash<int>()(state.a) ^ hash<int>()(state.b);
    }
};

class BestFirstSearch
{
public:
    static int aCapacity;
    static int bCapacity;
    static int targetAmount;

    static bool isGoalState(const State &state)
    {
        return state.a == targetAmount || state.b == targetAmount;
    }

    static vector<State> getSuccessors(const State &currentState)
    {
        vector<State> successors;

        // Fill Jug A
        successors.push_back(State(aCapacity, currentState.b));

        // Fill Jug B
        successors.push_back(State(currentState.a, bCapacity));

        // Empty Jug A
        successors.push_back(State(0, currentState.b));

        // Empty Jug B
        successors.push_back(State(currentState.a, 0));

        // Pour from A to B
        int pourAmount = min(currentState.a, bCapacity - currentState.b);
        successors.push_back(State(currentState.a - pourAmount, currentState.b + pourAmount));

        // Pour from B to A
        pourAmount = min(aCapacity - currentState.a, currentState.b);
        successors.push_back(State(currentState.a + pourAmount, currentState.b - pourAmount));

        return successors;
    }

    static int heuristic(const State &state)
    {
        return abs(state.a - targetAmount) + abs(state.b - targetAmount);
    }
};

int BestFirstSearch::aCapacity = 4;    // Jug A capacity
int BestFirstSearch::bCapacity = 3;    // Jug B capacity
int BestFirstSearch::targetAmount = 2; // Target amount of water

int main()
{
    auto cmp = [](const State &lhs, const State &rhs)
    {
        return BestFirstSearch::heuristic(lhs) > BestFirstSearch::heuristic(rhs);
    };

    priority_queue<State, vector<State>, decltype(cmp)> queue(cmp);
    unordered_set<State, StateHash> visited;

    State initialState(0, 0);
    queue.push(initialState);

    while (!queue.empty())
    {
        State currentState = queue.top();
        queue.pop();
        cout << "Visiting state: (" << currentState.a << ", " << currentState.b << ")" << endl;

        if (BestFirstSearch::isGoalState(currentState))
        {
            cout << "Goal state reached: (" << currentState.a << ", " << currentState.b << ")" << endl;
            break;
        }

        visited.insert(currentState);
        vector<State> successors = BestFirstSearch::getSuccessors(currentState);
        for (const auto &successor : successors)
        {
            if (visited.find(successor) == visited.end())
            {
                queue.push(successor);
            }
        }
    }

    return 0;
}

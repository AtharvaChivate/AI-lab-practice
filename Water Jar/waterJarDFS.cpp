#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct State
{
    int jar4;
    int jar3;
    State(int j4, int j3) : jar4(j4), jar3(j3) {}
};

vector<State> generateNextStates(State state)
{
    vector<State> next_states;

    // Fill jar4
    next_states.push_back(State(4, state.jar3));

    // Fill jar3
    next_states.push_back(State(state.jar4, 3));

    // Empty jar4
    next_states.push_back(State(0, state.jar3));

    // Empty jar3
    next_states.push_back(State(state.jar4, 0));

    // Pour water from jar4 to jar3
    int pour_amount = min(state.jar4, 3 - state.jar3);
    next_states.push_back(State(state.jar4 - pour_amount, state.jar3 + pour_amount));

    // Pour water from jar3 to jar4
    pour_amount = min(state.jar3, 4 - state.jar4);
    next_states.push_back(State(state.jar4 + pour_amount, state.jar3 - pour_amount));

    return next_states;
}

bool dfs(State start_state, unordered_set<string> &visited, stack<State> &path, int target)
{
    if (start_state.jar4 == target || start_state.jar3 == target)
    {
        path.push(start_state);
        return true;
    }

    string state_hash = to_string(start_state.jar4) + "," + to_string(start_state.jar3);
    if (visited.count(state_hash) > 0)
    {
        return false;
    }
    visited.insert(state_hash);

    vector<State> next_states = generateNextStates(start_state);
    for (const auto &next_state : next_states)
    {
        if (dfs(next_state, visited, path, target))
        {
            path.push(start_state);
            return true;
        }
    }

    return false;
}

int main()
{
    int capacity_jar4 = 4;
    int capacity_jar3 = 3;
    int desired_quantity = 2;

    State start_state(0, 0);
    unordered_set<string> visited;
    stack<State> path;

    cout << "***Water Jar Problem Using DFS***\n"
         << endl;
    cout << "Input - 4L and 3L Jars \nOutput - 2L \n"
         << endl;

    if (dfs(start_state, visited, path, desired_quantity))
    {
        cout << "\nPath from initial state "
                "to solution state ::"
             << endl;
        cout << "\nJar1   Jar2" << endl;
        while (!path.empty())
        {
            State state = path.top();
            path.pop();

            cout << state.jar4 << " \t" << state.jar3 << endl;
        }
    }
    else
    {
        cout << "No solution found." << endl;
    }

    return 0;
}

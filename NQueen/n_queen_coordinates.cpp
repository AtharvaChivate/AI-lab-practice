#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class NQueens {
private:
    int size;
    vector<vector<pair<int, int>>> solutions;

    bool isConflict(const vector<pair<int, int>>& queens) {
        for (size_t i = 0; i < queens.size(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (queens[i].first == queens[j].first ||
                    queens[i].second == queens[j].second ||
                    abs(queens[i].first - queens[j].first) == abs(queens[i].second - queens[j].second)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    NQueens(int n) : size(n) {}

    vector<vector<pair<int, int>>> solveDFS() {
        solutions.clear();
        stack<vector<pair<int, int>>> stack;
        stack.push({});

        while (!stack.empty()) {
            auto solution = stack.top();
            stack.pop();

            if (solution.size() == size) {
                solutions.push_back(solution);
                continue;
            }

            for (int col = 0; col < size; ++col) {
                solution.push_back({solution.size(), col});
                if (!isConflict(solution)) {
                    stack.push(solution);
                }
                solution.pop_back();
            }
        }

        return solutions;
    }

    vector<vector<pair<int, int>>> solveBFS() {
        solutions.clear();
        queue<vector<pair<int, int>>> queue;
        queue.push({});

        while (!queue.empty()) {
            auto solution = queue.front();
            queue.pop();

            if (solution.size() == size) {
                solutions.push_back(solution);
                continue;
            }

            for (int col = 0; col < size; ++col) {
                solution.push_back({solution.size(), col});
                if (!isConflict(solution)) {
                    queue.push(solution);
                }
                solution.pop_back();
            }
        }

        return solutions;
    }
};

int main() {
    int n;
    cout << "Enter the size of the board: ";
    cin >> n;

    NQueens nQueens(n);
    auto dfsSolutions = nQueens.solveDFS();
    auto bfsSolutions = nQueens.solveBFS();

    cout << "DFS Solutions: " << endl;
    for (const auto& sol : dfsSolutions) {
        for (const auto& q : sol) {
            cout << "(" << q.first << ", " << q.second << ") ";
        }
        cout << endl;
    }

    cout << "BFS Solutions: " << endl;
    for (const auto& sol : bfsSolutions) {
        for (const auto& q : sol) {
            cout << "(" << q.first << ", " << q.second << ") ";
        }
        cout << endl;
    }

    return 0;
}

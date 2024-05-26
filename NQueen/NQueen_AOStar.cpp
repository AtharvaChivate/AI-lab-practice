#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class AOStarNQueens
{
private:
    int N;

    struct Node
    {
        vector<int> queens;
        int g;
        int h;
        int f;
        vector<Node *> children;

        Node(vector<int> queens, int g, int h) : queens(queens), g(g), h(h), f(g + h) {}
    };

public:
    AOStarNQueens(int N) : N(N) {}

    vector<int> solve()
    {
        Node *root = new Node(vector<int>(N, -1), 0, 0);
        return aoStar(root);
    }

private:
    vector<int> aoStar(Node *node)
    {
        if (node->g == N)
        {
            return node->queens; // Solution found
        }

        if (node->children.empty())
        {
            expandNode(node);
        }

        for (Node *child : node->children)
        {
            vector<int> result = aoStar(child);
            if (!result.empty())
            {
                return result;
            }
        }

        return vector<int>(); // No solution found
    }

    void expandNode(Node *node)
    {
        int currentRow = node->g;
        for (int col = 0; col < N; col++)
        {
            if (isValid(node->queens, currentRow, col))
            {
                vector<int> newQueens = node->queens;
                newQueens[currentRow] = col;
                int newHeuristic = calculateHeuristic(newQueens, currentRow + 1);
                Node *newNode = new Node(newQueens, currentRow + 1, newHeuristic);
                node->children.push_back(newNode);
            }
        }
    }

    bool isValid(const vector<int> &queens, int row, int col)
    {
        for (int i = 0; i < row; i++)
        {
            if (queens[i] == col || abs(queens[i] - col) == row - i)
            {
                return false;
            }
        }
        return true;
    }

    int calculateHeuristic(const vector<int> &queens, int g)
    {
        int conflicts = 0;
        for (int i = 0; i < g; i++)
        {
            for (int j = i + 1; j < g; j++)
            {
                if (queens[i] == queens[j] || abs(queens[i] - queens[j]) == j - i)
                {
                    conflicts++;
                }
            }
        }
        return conflicts;
    }
};

int main()
{
    int N = 4;
    AOStarNQueens solver(N);
    vector<int> solution = solver.solve();

    if (!solution.empty())
    {
        cout << "Solution found:\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (solution[i] == j)
                {
                    cout << "Q ";
                }
                else
                {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution found." << endl;
    }

    return 0;
}

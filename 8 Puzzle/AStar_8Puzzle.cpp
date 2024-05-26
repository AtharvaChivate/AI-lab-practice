#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class AStarNode
{
public:
    vector<vector<int>> board;
    int zeroRow, zeroCol;
    int g; // cost to reach this node
    int h; // heuristic estimate of the cost to the goal
    int f; // f(n) = g(n) + h(n)
    AStarNode *parent;

    AStarNode(vector<vector<int>> board, int g, int h, AStarNode *parent)
        : board(board), g(g), h(h), f(g + h), parent(parent)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == 0)
                {
                    zeroRow = i;
                    zeroCol = j;
                }
            }
        }
    }

    vector<AStarNode *> neighbors()
    {
        vector<AStarNode *> neighbors;
        vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

        for (auto move : moves)
        {
            int newRow = zeroRow + move.first;
            int newCol = zeroCol + move.second;

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3)
            {
                vector<vector<int>> newBoard = board;
                swap(newBoard[zeroRow][zeroCol], newBoard[newRow][newCol]);

                AStarNode *neighborNode = new AStarNode(newBoard, g + 1, calculateHeuristic(newBoard), this);
                neighbors.push_back(neighborNode);
            }
        }

        return neighbors;
    }

    bool isGoal()
    {
        int count = 1;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] != count % 9)
                {
                    return false;
                }
                ++count;
            }
        }
        return true;
    }

    int calculateHeuristic(vector<vector<int>> &board)
    {
        // Simple heuristic: count the number of misplaced tiles
        int misplacedTiles = 0;
        int count = 1;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] != count % 9)
                {
                    ++misplacedTiles;
                }
                ++count;
            }
        }
        return misplacedTiles;
    }

    bool operator<(const AStarNode &other) const
    {
        return f > other.f; // For priority_queue, we need to invert the comparison
    }

    bool operator==(const AStarNode &other) const
    {
        return board == other.board;
    }
};

struct AStarNodeComparator
{
    bool operator()(const AStarNode *lhs, const AStarNode *rhs) const
    {
        return *lhs < *rhs;
    }
};

struct AStarNodeHasher
{
    size_t operator()(const AStarNode *node) const
    {
        size_t hash = 0;
        for (const auto &row : node->board)
        {
            for (int num : row)
            {
                hash = hash * 31 + num;
            }
        }
        return hash;
    }
};

class AStarSolver
{
public:
    AStarNode *initialNode;
    AStarNode *goalNode;

    AStarSolver(AStarNode *initialNode, AStarNode *goalNode) : initialNode(initialNode), goalNode(goalNode) {}

    void solve()
    {
        priority_queue<AStarNode *, vector<AStarNode *>, AStarNodeComparator> openSet;
        set<vector<vector<int>>> closedSet;

        openSet.push(initialNode);

        while (!openSet.empty())
        {
            AStarNode *currentNode = openSet.top();
            openSet.pop();

            if (currentNode->isGoal())
            {
                printMoves(currentNode);
                return;
            }

            closedSet.insert(currentNode->board);

            for (AStarNode *neighbor : currentNode->neighbors())
            {
                if (closedSet.find(neighbor->board) != closedSet.end())
                {
                    continue; // skip already evaluated neighbors
                }

                openSet.push(neighbor);
            }
        }

        cout << "No solution found." << endl;
    }

    void printMoves(AStarNode *goalNode)
    {
        cout << "Moves:" << endl;

        printMovesRecursive(goalNode);
    }

    void printMovesRecursive(AStarNode *node)
    {
        if (node == nullptr)
        {
            return;
        }

        printMovesRecursive(node->parent);
        printBoard(node);
        cout << endl;
    }

    void printBoard(AStarNode *node)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                cout << node->board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    vector<vector<int>> initialBoard = {{1, 2, 3}, {4, 0, 5}, {6, 7, 8}};
    vector<vector<int>> goalBoard = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    AStarNode *initialNode = new AStarNode(initialBoard, 0, 0, nullptr);
    AStarNode *goalNode = new AStarNode(goalBoard, 0, 0, nullptr);

    AStarSolver solver(initialNode, goalNode);
    solver.solve();
    return 0;
}

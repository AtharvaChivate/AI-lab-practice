#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct AOStarNode
{
    vector<vector<int>> board;
    int zeroRow, zeroCol;
    int g;    // cost to reach this node
    double h; // heuristic estimate of the cost to the goal
    double f; // f(n) = g(n) + h(n)
    AOStarNode *parent;

    AOStarNode(vector<vector<int>> &board, int g, double h, AOStarNode *parent)
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

    bool operator==(const AOStarNode &other) const
    {
        return board == other.board;
    }

    vector<AOStarNode *> neighbors()
    {
        vector<AOStarNode *> neighbors;

        int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

        for (const auto &move : moves)
        {
            int newRow = zeroRow + move[0];
            int newCol = zeroCol + move[1];

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3)
            {
                vector<vector<int>> newBoard = board;
                swap(newBoard[zeroRow][zeroCol], newBoard[newRow][newCol]);

                AOStarNode *neighborNode = new AOStarNode(newBoard, g + 1, calculateHeuristic(newBoard), this);
                neighbors.push_back(neighborNode);
            }
        }

        return neighbors;
    }

private:
    double calculateHeuristic(vector<vector<int>> &board)
    {
        // Simple heuristic: count the number of misplaced tiles
        int misplacedTiles = 0;
        int count = 1;
        for (const auto &row : board)
        {
            for (int val : row)
            {
                if (val != count % 9)
                {
                    misplacedTiles++;
                }
                count++;
            }
        }
        return misplacedTiles;
    }
};

struct AOStarNodeHash
{
    size_t operator()(const AOStarNode *node) const
    {
        size_t hash = 0;
        for (const auto &row : node->board)
        {
            for (int val : row)
            {
                hash ^= hash << 6 ^ val + 0x9e3779b9 + (hash >> 2);
            }
        }
        return hash;
    }
};

class AOStarComparator
{
public:
    bool operator()(const AOStarNode *a, const AOStarNode *b) const
    {
        return a->f > b->f; // Min heap
    }
};

class AOStarSolver
{
private:
    AOStarNode *initialNode;
    AOStarNode *goalNode;

public:
    AOStarSolver(AOStarNode *initialNode, AOStarNode *goalNode)
        : initialNode(initialNode), goalNode(goalNode) {}

    void solve()
    {
        priority_queue<AOStarNode *, vector<AOStarNode *>, AOStarComparator> openSet;
        unordered_set<AOStarNode *, AOStarNodeHash> closedSet;

        openSet.push(initialNode);

        while (!openSet.empty())
        {
            AOStarNode *currentNode = openSet.top();
            openSet.pop();

            if (*currentNode == *goalNode)
            {
                printMoves(currentNode);
                return;
            }

            closedSet.insert(currentNode);

            for (AOStarNode *neighbor : currentNode->neighbors())
            {
                if (closedSet.find(neighbor) != closedSet.end())
                {
                    continue; // skip already evaluated neighbors
                }

                if (!existsInPriorityQueue(openSet, neighbor))
                {
                    openSet.push(neighbor);
                }
            }
        }

        cout << "No solution found." << endl;
    }

private:
    bool existsInPriorityQueue(priority_queue<AOStarNode *, vector<AOStarNode *>, AOStarComparator> &pq, AOStarNode *node)
    {
        auto container = pq;
        while (!container.empty())
        {
            AOStarNode *top = container.top();
            container.pop();
            if (*top == *node)
                return true;
        }
        return false;
    }

    void printMoves(AOStarNode *goalNode)
    {
        cout << "Moves:" << endl;
        printMovesRecursive(goalNode);
    }

    void printMovesRecursive(AOStarNode *node)
    {
        if (node == nullptr)
        {
            return;
        }

        printMovesRecursive(node->parent);
        printBoard(node);
        cout << endl;
    }

    void printBoard(AOStarNode *node)
    {
        for (const auto &row : node->board)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    vector<vector<int>> initialBoard = {
        {1, 2, 3},
        {4, 0, 5},
        {6, 7, 8}};

    vector<vector<int>> goalBoard = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}};

    AOStarNode *initialNode = new AOStarNode(initialBoard, 0, 0, nullptr);
    AOStarNode *goalNode = new AOStarNode(goalBoard, 0, 0, nullptr);

    AOStarSolver solver(initialNode, goalNode);
    solver.solve();

    delete initialNode;
    delete goalNode;

    return 0;
}

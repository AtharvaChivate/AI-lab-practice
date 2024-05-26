#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

// Node class to represent a state in the search space
class Node
{
public:
    int x;         // first jug
    int y;         // second jug
    int cost;      // Cost to reach this node
    int heuristic;
    Node *parent; 

    Node(int x, int y, int cost, int heuristic, Node *parent)
    {
        this->x = x;
        this->y = y;
        this->cost = cost;
        this->heuristic = heuristic;
        this->parent = parent;
    }
};

// Custom comparator to order nodes by their total cost (cost + heuristic)
class NodeComparator
{
public:
    bool operator()(const Node *n1, const Node *n2) const
    {
        return (n1->cost + n1->heuristic) > (n2->cost + n2->heuristic);
    }
};

void solveAStar(int jug1, int jug2, int target)
{
    priority_queue<Node *, vector<Node *>, NodeComparator> pq;

    // Add the initial state to the priority queue
    pq.push(new Node(0, 0, 0, abs(0 - target) + abs(0 - target), nullptr));

    vector<vector<bool>> visited(jug1 + 1, vector<bool>(jug2 + 1, false)); 
    int totalNodes = 0; // Count of total Nodes explored                                                     

    while (!pq.empty())
    {
        Node *current = pq.top(); // Get the Node with the lowest total cost
        pq.pop();
        int curX = current->x;
        int curY = current->y;

        // Check if the goal state is reached
        if (curX == target || curY == target)
        {
            // Print the solution path
            stack<Node *> path;
            while (current != nullptr)
            {
                path.push(current);
                current = current->parent;
            }

            while (!path.empty())
            {
                Node *n = path.top();
                path.pop();
                cout << "(" << n->x << ", " << n->y << ")" << endl;
            }
            cout << "Total Nodes visited: " << totalNodes << endl;
            return;
        }

        // Skip visited Nodes
        if (visited[curX][curY])
        {
            continue;
        }
        visited[curX][curY] = true; // Mark current state as visited
        totalNodes++;

        // Generate and enqueue new states by filling and emptying the jugs
        // Fill the jugs
        pq.push(new Node(jug1, curY, current->cost + 1, abs(jug1 - target) + abs(curY - target), current));
        pq.push(new Node(curX, jug2, current->cost + 1, abs(curX - target) + abs(jug2 - target), current));

        // Empty the jugs
        pq.push(new Node(0, curY, current->cost + 1, abs(0 - target) + abs(curY - target), current));
        pq.push(new Node(curX, 0, current->cost + 1, abs(curX - target) + abs(0 - target), current));

        // Pour water from one jug to another
        int pourXToY = min(curX + curY, jug2);
        int pourYToX = min(curX + curY, jug1);
        pq.push(new Node(curX - (pourXToY - curY), pourXToY, current->cost + 1, abs(curX - (pourXToY - curY) - target) + abs(pourXToY - target), current));
        pq.push(new Node(pourYToX, curY - (pourYToX - curX), current->cost + 1, abs(pourYToX - target) + abs(curY - (pourYToX - curX) - target), current));
    }

    cout << "No solution" << endl;
}

int main()
{
    solveAStar(4, 3, 2); // Solve the water jug problem using A*
    return 0;
}

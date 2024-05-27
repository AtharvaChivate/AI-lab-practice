#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

using namespace std;

#define Width 3
#define Height 3

class State
{
public:
    State();
    State(int tiles2D[Width][Height]);
    int getValue(int x, int y);
    void setValue(int x, int y, int value);
    State operator=(State);
    bool operator==(const State &) const;
    friend bool operator<(const State &a, const State &o);
    string toString() const;
    string getPath();
    int getBlankX();
    int getBlankY();
    vector<State> expand();
    void setParent(State *p);
    State *getParent();

private:
    int tiles2D[Width][Height];
    vector<string> path;
    State *parent;
};

State::State() : parent(nullptr) {}

State::State(int tiles2D[Width][Height]) : parent(nullptr)
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            setValue(i, j, tiles2D[i][j]);
        }
    }
}

int State::getValue(int x, int y)
{
    return tiles2D[x][y];
}

void State::setValue(int x, int y, int value)
{
    tiles2D[x][y] = value;
}

State State::operator=(State myState)
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            setValue(i, j, myState.getValue(i, j));
        }
    }
    path = myState.path;
    parent = myState.parent;
    return *this;
}

bool State::operator==(const State &myState) const
{
    bool result = true;
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] != myState.tiles2D[i][j])
            {
                result = false;
            }
        }
    }
    return result;
}

bool operator<(const State &a, const State &o)
{
    return (a.toString() < o.toString());
}

string State::toString() const
{
    stringstream stringToReturn;
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] != 0)
            {
                stringToReturn << tiles2D[i][j] << " ";
            }
            else
            {
                stringToReturn << "  ";
            }
        }
        stringToReturn << endl;
    }
    return stringToReturn.str();
}

string State::getPath()
{
    unsigned i;
    string s;
    if (path.size() > 0)
    {
        for (i = 0; i < path.size() - 1; i++)
            s += path.at(i) + ", ";
        s += path.at(i) + "\n";
    }
    return s;
}

int State::getBlankX()
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] == 0)
            {
                return j;
            }
        }
    }
    return -1; // return -1 if not found, although it should always be found
}

int State::getBlankY()
{
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (tiles2D[i][j] == 0)
            {
                return i;
            }
        }
    }
    return -1; // return -1 if not found, although it should always be found
}

void State::setParent(State *p)
{
    parent = p;
}

State *State::getParent()
{
    return parent;
}

vector<State> State::expand()
{
    vector<State> children;
    int blankX = getBlankX();
    int blankY = getBlankY();
    State child;

    if (blankY > 0) // Move up
    {
        child = *this;
        swap(child.tiles2D[blankY][blankX], child.tiles2D[blankY - 1][blankX]);
        child.path.push_back("moveUp");
        child.setParent(this);
        children.push_back(child);
    }
    if (blankY < Height - 1) // Move down
    {
        child = *this;
        swap(child.tiles2D[blankY][blankX], child.tiles2D[blankY + 1][blankX]);
        child.path.push_back("moveDown");
        child.setParent(this);
        children.push_back(child);
    }
    if (blankX > 0) // Move left
    {
        child = *this;
        swap(child.tiles2D[blankY][blankX], child.tiles2D[blankY][blankX - 1]);
        child.path.push_back("moveLeft");
        child.setParent(this);
        children.push_back(child);
    }
    if (blankX < Width - 1) // Move right
    {
        child = *this;
        swap(child.tiles2D[blankY][blankX], child.tiles2D[blankY][blankX + 1]);
        child.path.push_back("moveRight");
        child.setParent(this);
        children.push_back(child);
    }
    return children;
}

void printSolutionPath(State *state)
{
    if (state == nullptr)
    {
        return;
    }
    printSolutionPath(state->getParent());
    cout << state->toString() << endl;
}

bool DFS(const State &goal, stack<State> &agenda, set<State> &closed, State &solution)
{
    State s;
    if (agenda.empty())
        return false;
    s = agenda.top();
    agenda.pop();

    cout << "Current state (DFS):" << endl;
    cout << s.toString() << endl;

    if (s == goal)
    {
        solution = s;
        printSolutionPath(&solution);
        return true;
    }
    if (closed.size() == 0 || (closed.find(s) == closed.end()))
    {
        vector<State> children;
        children = s.expand();
        closed.insert(s);
        for (int i = children.size() - 1; i >= 0; i--)
            agenda.push(children.at(i));
    }
    return DFS(goal, agenda, closed, solution);
}

bool BFS(const State &goal, queue<State> &agenda, set<State> &closed, State &solution)
{
    State s;
    if (agenda.empty())
        return false;
    s = agenda.front();
    agenda.pop();

    cout << "Current state (BFS):" << endl;
    cout << s.toString() << endl;

    if (s == goal)
    {
        solution = s;
        printSolutionPath(&solution);
        return true;
    }
    if (closed.size() == 0 || (closed.find(s) == closed.end()))
    {
        vector<State> children;
        children = s.expand();
        closed.insert(s);
        for (int i = children.size() - 1; i >= 0; i--)
            agenda.push(children.at(i));
    }
    return BFS(goal, agenda, closed, solution);
}

int main()
{
    cout << "// 8 Puzzle Solver //" << endl
         << endl
         << endl;

    int initialTiles2D[3][3] = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}};

    int goalTiles2D[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}};

    State initial(initialTiles2D);
    State goal(goalTiles2D);

    cout << "Initial puzzle:" << endl;
    cout << initial.toString();
    cout << endl;

    cout << "Goal puzzle:" << endl;
    cout << goal.toString();
    ;
    cout << endl;

    stack<State> agendaDFS;
    set<State> closedDFS;
    agendaDFS.push(initial);
    State solutionDFS;
    if (!DFS(goal, agendaDFS, closedDFS, solutionDFS))
    {
        cout << "No solution found with DFS." << endl;
    }

    cout << endl
         << endl;

    queue<State> agendaBFS;
    set<State> closedBFS;
    agendaBFS.push(initial);
    State solutionBFS;
    if (!BFS(goal, agendaBFS, closedBFS, solutionBFS))
    {
        cout << "No solution found with BFS." << endl;
    }

    return 0;
}
